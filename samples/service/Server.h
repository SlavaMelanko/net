#pragma once

#include <zmq.hpp>

#include <thread>

namespace net {
class IServer;
}

class Server
{
public:
  Server(zmq::context_t& context, std::string_view host, const uint32_t port);
  ~Server();

  void run();

private:
  std::unique_ptr<net::IServer> m_server;
  std::thread m_thread;
};
