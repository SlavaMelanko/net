#pragma once

namespace net {

class Broker
{
public:
  virtual ~Broker() noexcept = default;

  virtual void poll() = 0;
};

} // namespace net
