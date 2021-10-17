#pragma once

#include <memory>
#include <string_view>

namespace net {

class IRequestHandler;

class RequestHandlerFactory
{
public:
  virtual ~RequestHandlerFactory() noexcept = default;

  virtual std::unique_ptr<IRequestHandler> create(std::string_view action);
};

} // namespace net
