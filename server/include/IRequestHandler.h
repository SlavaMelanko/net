#pragma once

namespace net {

namespace json {
class Document;
}

class IRequestHandler
{
public:
  virtual ~IRequestHandler() noexcept = default;

  virtual void handle(const json::Document& document) = 0;
};

} // namespace net
