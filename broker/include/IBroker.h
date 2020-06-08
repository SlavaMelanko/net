#pragma once

namespace net {

class IBroker
{
public:
  virtual ~IBroker() noexcept = default;

  virtual void poll() = 0;
};

} // namespace net
