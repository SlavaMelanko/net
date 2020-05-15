#pragma once

#include <zmq.hpp>

#include <thread>

namespace net {
class Subscriber;
}

class NotificationConnection
{
public:
  NotificationConnection(zmq::context_t& context, const uint32_t port);
  ~NotificationConnection() noexcept;

  void run();

private:
  void process();

  std::unique_ptr<net::Subscriber> m_subscriber;
  std::thread m_thread;
};
