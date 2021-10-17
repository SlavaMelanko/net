#include "RequestHandlerFactory.h"

#include "HeartbeatRequestHandler.h"

#include <stdexcept>

namespace net {

std::unique_ptr<IRequestHandler> RequestHandlerFactory::create(std::string_view action)
{
  if (action == "heartbeat") {
    return std::make_unique<HeartbeatRequestHandler>();
  } else {
    throw std::invalid_argument{ "Unhandled action" };
  }
}

} // namespace net
