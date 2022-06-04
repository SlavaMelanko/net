#include "ZmqClient.h"

#include <Log.h>
#include <Randomizer.h>

#include <zhelpers.hpp>

namespace net {

namespace {

Identity GenerateRandomId()
{
  constexpr size_t length = 5;

  return utils::Randomizer{}.generate(length);
}

} // namespace

ZmqClient::ZmqClient(zmq::context_t& context, const ConnectionSettings& connectionSettings)
  : m_socket{ context, ZMQ_DEALER }
{
  setId(connectionSettings.id);
  connect(connectionSettings.host, connectionSettings.port);
  Log::info("OK, client's connection with server has been established");
}

std::string ZmqClient::send(const std::string& data)
{
  s_sendmore(m_socket, std::string{ "" }); // set delimiter
  s_send(m_socket, data);

  {
    s_recv(m_socket); // get delimiter
  }

  return s_recv(m_socket);
}

std::string ZmqClient::send(const std::string& metadata, const std::string& data)
{
  s_sendmore(m_socket, std::string{ "" }); // set delimiter
  s_sendmore(m_socket, metadata);
  s_sendmore(m_socket, std::string{ "" });
  s_send(m_socket, data);

  {
    s_recv(m_socket); // get delimiter
  }

  return s_recv(m_socket);
}

std::string ZmqClient::setId(const IdentityOpt& id)
{
  const auto identity = id.value_or(GenerateRandomId());
  Log::info("Client ID is \"{}\"", identity);
  m_socket.setsockopt(ZMQ_IDENTITY, identity.c_str(), identity.length());

  return identity;
}

void ZmqClient::connect(std::string_view host, const uint16_t port)
{
  const std::string address = fmt::format("tcp://{}:{}", host, port);
  Log::info("Client is connecting to {}", address);
  m_socket.connect(address);
}

} // namespace net
