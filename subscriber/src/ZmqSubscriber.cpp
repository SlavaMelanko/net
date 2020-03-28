#include "ZmqSubscriber.h"

#include <Log.h>

#include <zhelpers.hpp>

namespace net {

ZmqSubscriber::ZmqSubscriber(zmq::context_t& context, std::string_view host, const uint16_t port)
  : m_socket{ context, ZMQ_SUB }
{
  const std::string address = fmt::format("tcp://{}:{}", host, port);
  INFO("Subscriber is connecting to {}", address);
  m_socket.connect(address);
  INFO("OK, subscriber is ready");
}

void ZmqSubscriber::subscribeTo(const std::string& topic)
{
  m_socket.setsockopt(ZMQ_SUBSCRIBE, topic.c_str(), topic.size());
}

void ZmqSubscriber::subscribeToAllTopics()
{
  subscribeTo("");
}

std::string ZmqSubscriber::waitForNotification()
{
  const auto topic = s_recv(m_socket);
  const auto content = s_recv(m_socket);

  INFO("{}: {}", topic, content);

  return content;
}

} // namespace net
