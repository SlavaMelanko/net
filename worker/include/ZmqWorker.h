#pragma once

#include "Worker.h"

#include <zmq.hpp>

namespace net {

class ZmqWorker : public Worker
{
public:
  ZmqWorker(zmq::context_t& context, std::string_view host, const uint16_t port);
  ZmqWorker(zmq::context_t& context, const uint16_t port);

  void process() override;

private:
  zmq::socket_t m_socket;
};

} // namespace net
