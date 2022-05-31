#include "ConnectionSettings.h"

namespace net {

ConnectionSettings MakeConnectionSettings(const std::string& id,
                                          const std::string& host,
                                          const uint32_t port)
{
  ConnectionSettings connectionSettings;

  if (!id.empty())
    connectionSettings.id = id;
  if (!host.empty())
    connectionSettings.host = host;
  connectionSettings.port = port;

  return connectionSettings;
}

ConnectionSettings MakeConnectionSettings(const std::string& id, const uint32_t port)
{
  return MakeConnectionSettings(id, "", port);
}

ConnectionSettings MakeConnectionSettings(const uint32_t port)
{
  return MakeConnectionSettings("", port);
}

} // namespace net
