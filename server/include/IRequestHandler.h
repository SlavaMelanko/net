#pragma once

#include "Request.h"

namespace net {

class IRequestHandler
{
public:
  virtual ~IRequestHandler() noexcept = default;

  virtual json::Document process(const Request& request) const = 0;
};

} // namespace net
