#pragma once

#include "Server.h"

#include <zmq.hpp>

namespace net {

class ZmqServer : public Server
{
public:
  ZmqServer(zmq::context_t& context, std::string_view host, const uint16_t port);

  void run() override;

private:
  zmq::socket_t m_socket;
};

} // namespace net
