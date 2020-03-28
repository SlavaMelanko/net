#pragma once

#include <memory>
#include <string>

namespace net {

class Client
{
public:
  virtual ~Client() noexcept = default;

  virtual std::string send(const std::string& data) = 0;
};

using ClientUnPtr = std::unique_ptr<Client>;

} // namespace net
