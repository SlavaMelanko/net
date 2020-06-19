#pragma once

#include "IRequestHandler.h"

namespace net {

class HeartbeatRequestHandler : public IRequestHandler
{
public:
  void handle(const json::Document& document) override;
};

} // namespace net
