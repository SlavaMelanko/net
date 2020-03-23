#include "Server.h"

#include <Log.h>

#include <zhelpers.hpp>

namespace net {

Server::Server(zmq::context_t& context, const BindingSettings& settings)
  : m_server{ context, ZMQ_ROUTER }
{
  const std::string address = fmt::format("tcp://{}:{}", settings.address, settings.port);
  INFO("Binding to {}", address);
  m_server.bind(address);
}

void Server::run()
{
  const std::string identity = s_recv(m_server);
  const std::string delimiter = s_recv(m_server);
  const std::string message = s_recv(m_server);

  s_sendmore(m_server, identity);
  s_sendmore(m_server, delimiter);
  s_send(m_server, std::string{ "Hi client" });
}

} // namespace net
