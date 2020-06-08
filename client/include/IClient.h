#pragma once

#include <string>

namespace net {

class IClient
{
public:
  virtual ~IClient() noexcept = default;

  virtual std::string send(const std::string& data) = 0;
};

} // namespace net
