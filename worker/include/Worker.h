#pragma once

#include <memory>

namespace net {

class Worker
{
public:
  virtual ~Worker() noexcept = default;

  virtual void process() = 0;
};

using WorkerUnPtr = std::unique_ptr<Worker>;

} // namespace net
