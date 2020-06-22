#pragma once

#include "IRequestHandler.h"

namespace net {

class HeartbeatRequestHandler : public IRequestHandler
{
public:
  json::Document handle(const json::Document& request) override;
};

} // namespace net
