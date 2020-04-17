#pragma once

#include <memory>

namespace net {

class Server
{
public:
  virtual ~Server() noexcept = default;

  virtual void run() = 0;
};

using ServerUnPtr = std::unique_ptr<Server>;

} // namespace net
