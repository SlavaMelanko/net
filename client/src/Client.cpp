#include "Client.h"

#include <Log.h>
#include <Randomizer.h>

#include <zhelpers.hpp>

namespace net {

namespace {

Identity GenerateRandomId()
{
  constexpr size_t length = 5;
  return utils::Randomizer::generateString(length);
}

} // namespace

Client::Client(zmq::context_t& context, const Settings& settings)
  : m_client{ context, ZMQ_DEALER }
{
  setId(settings.id);
  connect(settings.host, settings.port);
}

std::string Client::setId(const std::optional<Identity>& id)
{
  const auto identity = id ? id.value() : GenerateRandomId();
  INFO("Client ID is \"{}\"", identity);
  m_client.setsockopt(ZMQ_IDENTITY, identity.c_str(), identity.length());

  return identity;
}

void Client::connect(std::string_view host, const uint16_t port)
{
  const std::string address = fmt::format("tcp://{}:{}", host, port);
  INFO("Client is connecting to {}", address);
  m_client.connect(address);
}

} // namespace net
