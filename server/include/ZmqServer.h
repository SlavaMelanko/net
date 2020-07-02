#pragma once

#include "IServer.h"
#include "Request.h"

#include <zmq.hpp>

namespace net {

class RequestHandlerFactory;

class ZmqServer : public IServer
{
public:
  ZmqServer(std::unique_ptr<RequestHandlerFactory> requestHandlerFactory,
            zmq::context_t& context,
            std::string_view host,
            const uint16_t port);

  void run() override;

private:
  Request receive();
  bool respond(const std::string& clientId,
               const std::string& delimiter,
               const std::string& response);

  void handleRequest();

  zmq::socket_t m_socket;
  std::unique_ptr<RequestHandlerFactory> m_requestHandlerFactory;
};

} // namespace net
