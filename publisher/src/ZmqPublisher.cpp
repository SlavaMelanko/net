#include "ZmqPublisher.h"

#include <Log.h>

#include <zhelpers.hpp>

#include <fmt/format.h>

#include <errno.h>

namespace net {

ZmqPublisher::ZmqPublisher(zmq::context_t& context, std::string_view host, const uint16_t port)
  : m_socket{ context, ZMQ_PUB }
{
  const std::string address = fmt::format("tcp://{}:{}", host, port);
  INFO("Publisher is binding to {}", address);
  m_socket.bind(address);
}

void ZmqPublisher::sendOut(const std::string& topic, const std::string& data)
{
  s_sendmore(m_socket, topic);
  s_send(m_socket, data);
}

void ZmqPublisher::broadcast(const std::string& data)
{
  return sendOut("", data);
}

} // namespace net
