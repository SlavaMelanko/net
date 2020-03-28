#pragma once

#include "Client.h"
#include "ConnectionSettings.h"

#include <zmq.hpp>

namespace net {

class ZmqClient : public Client
{
public:
  ZmqClient(zmq::context_t& context, const ConnectionSettings& connectionSettings);

  std::string send(const std::string& data) override;

private:
  std::string setId(const IdentityOpt& id);

  void connect(std::string_view host, const uint16_t port);

  zmq::socket_t m_socket;
};

} // namespace net
