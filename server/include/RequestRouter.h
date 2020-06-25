#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>

namespace net {

class IRequestHandler;

class RequestRouter
{
public:
  RequestRouter();

  bool add(const std::string& action, std::unique_ptr<IRequestHandler>&& requestHandler);

  std::shared_ptr<IRequestHandler> route(const std::string& action);

private:
  std::unordered_map<std::string, std::shared_ptr<IRequestHandler>> m_requestHandlers;
};

} // namespace net
