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
  request.action = s_recv(m_socket);
  request.delimiter = s_recv(m_socket);
  request.message = s_recv(m_socket);

  Log::info("#{}: @{} - \"{}\"", request.clientId, request.action, request.message.dump());

  return request;
}

bool ZmqServer::respond(const std::string& clientId,
                        const std::string& delimiter,
                        const std::string& response)
{
  s_sendmore(m_socket, clientId);
  s_sendmore(m_socket, delimiter);

  return s_send(m_socket, response);
}

void ZmqServer::handleRequest()
{
  const auto request = receive();

  auto handler = m_requestHandlerFactory->create(request.action);

  auto responseMessage = handler->process(request);

  respond(request.clientId, request.delimiter, responseMessage.dump());
}

} // namespace net
