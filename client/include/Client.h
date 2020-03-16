#pragma once

#include <optional>
#include <string>

#include <zmq.hpp>

namespace net {

struct Settings
{
  std::optional<int> id;
  std::optional<std::string> host;
  uint16_t port;
};

class Client
{
public:
  Client(zmq::context_t& context, const Settings& settings);

private:
  void setId(const std::optional<int>& id);
  void connect(const std::optional<std::string>& host, const uint16_t port);

  zmq::socket_t m_client;
};

} // namespace net
