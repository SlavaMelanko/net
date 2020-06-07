#pragma once

#include <zmq.hpp>

namespace net {
class Publisher;
}

class Publisher
{
public:
  Publisher(zmq::context_t& context, std::string_view host, const uint16_t port);
  ~Publisher();

  void run();
  void stop();

  bool push(std::string_view message, std::string_view topic = "");

private:
  std::unique_ptr<net::Publisher> m_publisher;
};
