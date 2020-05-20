#include "Service.h"

#include <ZmqServer.h>

Service::Service(zmq::context_t& context, const std::string_view host, const uint32_t port)
  : m_server{ std::make_unique<net::ZmqServer>(context, host, port) }
{}

Service::~Service()
{
  if (m_thread.joinable())
    m_thread.join();
}

void Service::run()
{
  m_thread = std::thread{ [this]() { m_server->run(); } };
}
