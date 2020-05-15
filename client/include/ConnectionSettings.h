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

ConnectionSettings MakeConnectionSettings(const std::string& id,
                                          const std::string& host,
                                          const uint32_t port);
/// Makes connection settings for localhost.
ConnectionSettings MakeConnectionSettings(const std::string& id, const uint32_t port);
/// Makes connection settings for localhost with random ID.
ConnectionSettings MakeConnectionSettings(const uint32_t port);

} // namespace net
