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
      handleRequest();
    } catch (zmq::error_t& e) {
      Log::error(e.what());
      if (e.num() == ETERM) break;
    }
  }
}

Request ZmqServer::receive()
{
  Request request;
  request.clientId = s_recv(m_socket);
  request.delimiter = s_recv(m_socket);
  request.message = s_recv(m_socket);

  Log::info("Client #{}: \"{}\"", request.clientId, request.message.dump());

  return request;
}

void ZmqServer::handleRequest()
{
  const auto request = receive();

  const auto action = request.message.getString("action").value();
  auto handler = m_requestHandlerFactory->create(action);

  auto responseMessage = handler->process(request);

  s_sendmore(m_socket, request.clientId);
  s_sendmore(m_socket, request.delimiter);
  s_send(m_socket, responseMessage.dump());
}

} // namespace net
