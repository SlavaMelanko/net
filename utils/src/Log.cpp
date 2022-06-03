#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace net {

namespace {

void InitializeConsoleLogger(const std::string& channelName)
{
  spdlog::stdout_color_mt(channelName);
  // Pattern flags https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
  spdlog::set_pattern("%d/%m/%Y %H:%M:%S.%e %L: %v");
}

} // namespace

std::string Log::m_channelName = "console";

bool Log::initialize() noexcept
{
  try {
    InitializeConsoleLogger(m_channelName);
  } catch (...) {
    return false;
  }

  return true;
}

std::shared_ptr<spdlog::logger> Log::get()
{
  return spdlog::get(m_channelName);
}

} // namespace net
