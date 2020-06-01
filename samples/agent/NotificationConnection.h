#pragma once

#include "Connection.h"

#include <zmq.hpp>

#include <thread>

namespace net {
class Subscriber;
}

class NotificationConnection : public Connection
{
public:
  NotificationConnection(zmq::context_t& context, const uint32_t port);
  ~NotificationConnection() noexcept;

  void run() override;

private:
  void process() override;

  std::unique_ptr<net::Subscriber> m_subscriber;
  std::thread m_thread;
};
