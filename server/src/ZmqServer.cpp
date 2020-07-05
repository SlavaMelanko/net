#include "ZmqServer.h"

#include "RequestHandlerFactory.h"

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
  auto clientId = s_recv(m_socket);
  auto delimiter = s_recv(m_socket);
  auto action = s_recv(m_socket);
  s_recv(m_socket); // skip the 2nd delimiter
  auto message = s_recv(m_socket);

  return Request{ clientId, delimiter, action, message };
}

bool ZmqServer::respond(const std::string& clientId,
                        const std::string& delimiter,
                        const json::Document& response)
{
  if (clientId.empty()) return false;

  s_sendmore(m_socket, clientId);
  s_sendmore(m_socket, delimiter);

  return s_send(m_socket, response.dump());
}

void ZmqServer::handleRequest()
{
  Request request;

  try {
    request = receive();

    auto handler = m_requestHandlerFactory->create(request.getAction());
    auto responseMessage = handler->process(request);

    respond(request.getClientId(), request.getDelimiter(), responseMessage);
  } catch (zmq::error_t& e) {
    if (e.num() == ETERM) throw;
  } catch (const std::exception& e) {
    Log::error(e.what());

    json::Document errorMessage;
    errorMessage.setBool("ok", false);
    errorMessage.setString("error", e.what());

    respond(request.getClientId(), request.getDelimiter(), errorMessage);
  }
}

} // namespace net
