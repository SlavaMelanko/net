#include "RequestRouter.h"

#include "HeartbeatRequestHandler.h"

namespace net {

RequestRouter::RequestRouter()
  : m_requestHandlers{ { "heartbeat", std::make_shared<HeartbeatRequestHandler>() } }
{}

bool RequestRouter::add(const std::string& action,
                        std::unique_ptr<IRequestHandler>&& requestHandler)
{
  const auto [iterator, ok] = m_requestHandlers.try_emplace(action, std::move(requestHandler));

  return ok;
}

std::shared_ptr<IRequestHandler> RequestRouter::route(const std::string& action)
{
  auto iterator = m_requestHandlers.find(action);

  return (iterator != m_requestHandlers.end()) ? iterator->second : nullptr;
}

} // namespace net
