#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace utils {

void InitLogging()
{
  spdlog::stdout_color_mt("stdout");
}

std::atomic_bool Log::m_initialized = false;
std::string Log::m_channel = "console";

void Log::initialize()
{
  spdlog::stdout_color_mt(m_channel);
  m_initialized = true;
}

} // namespace utils
