#include "ZmqPublisher.h"

#include <Log.h>

#include <zhelpers.hpp>

#include <fmt/format.h>

#include <errno.h>

namespace net {

ZmqPublisher::ZmqPublisher(zmq::context_t& context,
                           const std::string_view host,
                           const uint16_t port)
  : m_publisher{ context, ZMQ_PUB }
{
  const std::string address = fmt::format("tcp://{}:{}", host, port);
  INFO("Publisher is binding to {}", address);
  m_publisher.bind(address);
}

bool ZmqPublisher::sendOut(const std::string& topic, const std::string& data)
{
  if (!s_sendmore(m_publisher, topic) || !s_send(m_publisher, data)) {
    ERROR(zmq_strerror(errno));
    return false;
  }

  return true;
}

bool ZmqPublisher::broadcast(const std::string& data)
{
  return sendOut("", data);
}

} // namespace net
