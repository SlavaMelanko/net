#include "Service.h"

#include <ZmqServer.h>

Service::Service(zmq::context_t& context, const std::string_view host, const uint32_t port)
  : m_server{ std::make_unique<net::ZmqServer>(context, host, port) }
  , m_thread{ &Service::run, this }
{}

Service::~Service() {}

void Service::run()
{
  m_server->run();
}
