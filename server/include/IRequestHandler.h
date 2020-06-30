#pragma once

#include <Json.h>

namespace net {

class IRequestHandler
{
public:
  virtual ~IRequestHandler() noexcept = default;

  virtual json::Document process(const json::Document& request) = 0;
};

} // namespace net
