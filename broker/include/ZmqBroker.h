#pragma once

#include "IBroker.h"

#include <zmq.hpp>

namespace net {

class ZmqBroker : public IBroker
{
public:
  ZmqBroker(const uint32_t frontendPort, const uint32_t backendPort);

  void poll() override;

private:
  zmq::context_t m_context{ 1 };
  zmq::socket_t m_frontend{ m_context, ZMQ_ROUTER };
  zmq::socket_t m_backend{ m_context, ZMQ_DEALER };
};

} // namespace net
