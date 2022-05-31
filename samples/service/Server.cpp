#include "Server.h"

#include <RequestHandlerFactory.h>
#include <ZmqServer.h>

Server::Server(std::unique_ptr<net::RequestHandlerFactory> requestHandlerFactory,
               zmq::context_t& context,
               const std::string_view host,
               const uint32_t port)
  : m_server{
    std::make_unique<net::ZmqServer>(std::move(requestHandlerFactory), context, host, port)
  }
{}

Server::~Server()
{
  if (m_thread.joinable())
    m_thread.join();
}

void Server::run()
{
  m_thread = std::thread{ [this]() { m_server->run(); } };
}
