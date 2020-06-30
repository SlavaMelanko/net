#include "HeartbeatRequestHandler.h"

#include <zhelpers.hpp>

namespace net {

json::Document HeartbeatRequestHandler::process(const json::Document&)
{
  json::Document response;
  response.setString("srv_v", "0.0.1");
  response.setString("zmq_v", s_version());

  return std::move(response);
}

} // namespace net
