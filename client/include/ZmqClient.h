#pragma once

#include "ConnectionSettings.h"
#include "IClient.h"

#include <zmq.hpp>

namespace net {

class ZmqClient : public IClient
{
public:
  ZmqClient(zmq::context_t& context, const ConnectionSettings& connectionSettings);

  std::string send(const std::string& data) override;
  std::string send(const std::string& metadata, const std::string& data) override;

private:
  std::string setId(const IdentityOpt& id);

  void connect(std::string_view host, const uint16_t port);

  zmq::socket_t m_socket;
};

} // namespace net
