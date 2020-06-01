#pragma once

#include <zmq.hpp>

#include <thread>

namespace net {
class Publisher;
}

class Publisher
{
public:
  Publisher(zmq::context_t& context, std::string_view host, const uint16_t port);
  ~Publisher();

  void run();

private:
  void process();

  std::unique_ptr<net::Publisher> m_publisher;
  std::thread m_thread;
};
