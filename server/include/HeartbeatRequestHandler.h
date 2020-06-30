#pragma once

#include "IRequestHandler.h"

namespace net {

class HeartbeatRequestHandler : public IRequestHandler
{
public:
  json::Document process(std::string_view clientId, const json::Document& request) override;
};

} // namespace net
