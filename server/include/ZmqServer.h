#pragma once

#include "IServer.h"

#include <zmq.hpp>

namespace net {

class ZmqServer : public IServer
{
public:
  ZmqServer(zmq::context_t& context, std::string_view host, const uint16_t port);

  void run() override;

private:
  void handle();

  zmq::socket_t m_socket;
};

} // namespace net
