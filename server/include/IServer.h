#pragma once

namespace net {

class IServer
{
public:
  virtual ~IServer() noexcept = default;

  virtual void run() = 0;
};

} // namespace net
