#pragma once

#include <optional>
#include <string>

namespace net {

using Identity = std::string;
using IdentityOpt = std::optional<Identity>;

struct ConnectionSettings
{
  IdentityOpt id;
  std::string host{ "localhost" };
  uint16_t port;
};

} // namespace net
