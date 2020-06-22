#pragma once

#include <Json.h>

namespace net {

class IRequestHandler
{
public:
  virtual ~IRequestHandler() noexcept = default;

  virtual json::Document handle(const json::Document& request) = 0;
};

} // namespace net
