#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace net {

namespace {

auto InitializeConsoleLogger(const std::string& channelName)
{
  // Pattern flags https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
  spdlog::set_pattern("%d/%m/%Y %H:%M:%S.%e %L: %v");

  return spdlog::stdout_color_mt(channelName);;
}

} // namespace

bool Log::initialize() noexcept
{
  try {
    m_logger = InitializeConsoleLogger(m_channelName);
  } catch (...) {
    return false;
  }

  return true;
}

} // namespace net
