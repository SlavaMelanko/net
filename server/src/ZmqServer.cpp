#include "ZmqServer.h"

#include "RequestHandlerFactory.h"

#include <Json.h>
#include <Log.h>

#include <zhelpers.hpp>

namespace net {

ZmqServer::ZmqServer(std::unique_ptr<RequestHandlerFactory> requestHandlerFactory,
                     zmq::context_t& context,
                     std::string_view host,
                     const uint16_t port)
  : m_socket{ context, ZMQ_ROUTER }
  , m_requestHandlerFactory{ std::move(requestHandlerFactory) }
{
  const std::string address = fmt::format("tcp://{}:{}", host, port);
  Log::info("Server is binding to {}", address);
  m_socket.bind(address);
  Log::info("OK, server started to listen for incoming requests");
}

void ZmqServer::run()
{
  while (true) {
    try {
      handle();
    } catch (zmq::error_t& e) {
      Log::error(e.what());
      if (e.num() == ETERM) break;
    }
  }
}

void ZmqServer::handle()
{
  const std::string identity = s_recv(m_socket);
  const std::string delimiter = s_recv(m_socket);
  const std::string request = s_recv(m_socket);

  Log::info("Client #{}: \"{}\"", identity, request);

  const json::Document message{ request };

  const auto action = message.getString("action").value();

  auto handler = m_requestHandlerFactory->create(action);
  auto response = handler->process(identity, message);

  s_sendmore(m_socket, identity);
  s_sendmore(m_socket, delimiter);
  s_send(m_socket, response.dump());
}

} // namespace net
