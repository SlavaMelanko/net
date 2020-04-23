#include "ZmqBroker.h"

#include <Log.h>

#include <zhelpers.hpp>

namespace net {

ZmqBroker::ZmqBroker(const uint32_t frontendPort, const uint32_t backendPort)
{
  const auto frontendAddress = fmt::format("tcp://*:{}", frontendPort);
  Log::info("Binding frontend to {}", frontendAddress);
  m_frontend.bind(frontendAddress);

  const auto backendAddress = fmt::format("tcp://*:{}", backendPort);
  Log::info("Binding backend to {}", backendAddress);
  m_backend.bind(backendAddress);
}

void ZmqBroker::poll()
{
  zmq::proxy(m_frontend, m_backend);
}

} // namespace net
