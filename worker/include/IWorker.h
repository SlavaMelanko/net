#pragma once

namespace net {

class IWorker
{
public:
  virtual ~IWorker() noexcept = default;

  virtual void process() = 0;
};

} // namespace net
