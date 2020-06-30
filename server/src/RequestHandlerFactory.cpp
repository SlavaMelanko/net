#include "RequestHandlerFactory.h"

namespace net {

std::unique_ptr<IRequestHandler> RequestHandlerFactory::create(std::string_view action)
{
  if (action == "heartbeat") {
    return std::make_unique<HeartbeatRequestHandler>();
  } else {
    return nullptr;
  }
}

} // namespace net
