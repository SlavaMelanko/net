#pragma once

#include <optional>
#include <string>

#include <zmq.hpp>

namespace net {

using Identity = std::string;

struct Settings
{
  std::optional<Identity> id;
  /**
   Host address which can be either IP or domain name.
   If value is not set then connection to localhost will be used.
  */
  std::string host{ "localhost" };
  uint16_t port{ 5555 };
};

class Client
{
public:
  Client(zmq::context_t& context, const Settings& settings);

private:
  std::string setId(const std::optional<Identity>& id);
  void connect(std::string_view host, const uint16_t port);

  zmq::socket_t m_client;
};

} // namespace net
