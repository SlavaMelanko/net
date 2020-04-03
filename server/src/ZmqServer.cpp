#include "ZmqServer.h"

#include <Log.h>

#include <zhelpers.hpp>

namespace net {

ZmqServer::ZmqServer(zmq::context_t& context, std::string_view host, const uint16_t port)
  : m_socket{ context, ZMQ_ROUTER }
{
  const std::string address = fmt::format("tcp://{}:{}", host, port);
  utils::Log::info("Binding to {}", address);
  m_socket.bind(address);
  utils::Log::info("OK, listening for incoming connection requests...");
}

void ZmqServer::run()
{
  const std::string identity = s_recv(m_socket);
  const std::string delimiter = s_recv(m_socket);
  const std::string message = s_recv(m_socket);

  utils::Log::info("Client #{}: \"{}\"", identity, message);

  s_sendmore(m_socket, identity);
  s_sendmore(m_socket, delimiter);
  s_send(m_socket, message);
}

} // namespace net
