#pragma once

#include <Json.h>

#include <string>

namespace net {

struct Request
{
  std::string clientId;
  std::string delimiter;
  std::string action;
  json::Document message;
};

} // namespace net
