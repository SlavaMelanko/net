#include "Client.h"

#include <Log.h>

#include <zhelpers.hpp>

namespace net {

Client::Client(zmq::context_t& context, const Settings& settings)
  : m_client{ context, ZMQ_DEALER }
{
  setId(settings.id);
  connect(settings.host, settings.port);
}

void Client::setId(const std::optional<int>& id)
{
#if (defined(WIN32))
  s_set_id(m_client, static_cast<intptr_t>(id.value()));
#else
  s_set_id(m_client); // set a printable identity
#endif
}

void Client::connect(const std::optional<std::string>& host, const uint16_t port)
{
  const std::string address = fmt::format("tcp://{}:{}", host.value_or("localhost"), port);
  INFO("Client is connecting to {}", address);
  m_client.connect(address);
}

} // namespace net
