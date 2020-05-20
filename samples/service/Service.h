#pragma once

#include <zmq.hpp>

#include <thread>

namespace net {
class Server;
}

class Service
{
public:
  Service(zmq::context_t& context, std::string_view host, const uint32_t port);
  ~Service();

  void run();

private:
  std::unique_ptr<net::Server> m_server;
  std::thread m_thread;
};
