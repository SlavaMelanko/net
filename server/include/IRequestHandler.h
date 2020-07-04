#pragma once

#include "Request.h"

namespace net {

class IRequestHandler
{
public:
  IRequestHandler() noexcept = default;

  IRequestHandler(IRequestHandler&&) noexcept = default;
  IRequestHandler& operator=(IRequestHandler&&) noexcept = default;

  IRequestHandler(const IRequestHandler&) = delete;
  IRequestHandler& operator=(const IRequestHandler&) = delete;

  virtual ~IRequestHandler() noexcept = default;

  virtual json::Document process(const Request& request) const = 0;
};

} // namespace net
