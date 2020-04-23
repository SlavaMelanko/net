#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace net {

namespace {

void InitializeConsoleLogger(const std::string& channel)
{
  spdlog::stdout_color_mt(channel);
  // Pattern flags https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
  spdlog::set_pattern("%d/%m/%Y %H:%M:%S.%e %L: %v");
}

} // namespace

std::atomic_bool Log::m_initialized = false;
std::string Log::m_channel = "console";

void Log::initialize() noexcept
{
  InitializeConsoleLogger(m_channel);
  m_initialized = true;
}

} // namespace net
