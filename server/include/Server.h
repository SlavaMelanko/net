#pragma once

#include <zmq.hpp>

namespace net {

class Server
{
public:
  struct BindingSettings
  {
    BindingSettings() noexcept {};

    std::string address{ "127.0.0.1" };
    uint16_t port{ 5555 };
  };

  Server(zmq::context_t& context, const BindingSettings& settings = {});

  void run();

private:
  zmq::socket_t m_server;
};

} // namespace net
