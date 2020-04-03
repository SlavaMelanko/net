#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace utils {

namespace {
void InitializeConsoleLogger(const std::string& channel)
{
  spdlog::stdout_color_mt(channel);
}
}

std::atomic_bool Log::m_initialized = false;
std::string Log::m_channel = "console";

void Log::initialize()
{
  InitializeConsoleLogger(m_channel);
  m_initialized = true;
}

} // namespace utils
