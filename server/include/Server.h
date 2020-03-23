#pragma once

#include <zmq.hpp>

namespace net {

class Server
{
public:
  struct BindingSettings
  {
    std::string address{ "localhost" };
    uint16_t port{ 5555 };
  };

  Server(zmq::context_t& context, const BindingSettings& settings);

  void run();

private:
  zmq::socket_t m_server;
};

} // namespace net
