#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace net {

namespace {

auto CreateConsoleLogger(const std::string& channelName)
{
  auto logger = spdlog::stdout_color_mt(channelName);
  // Pattern flags https://github.com/gabime/spdlog/wiki/3.-Custom-formatting#pattern-flags
  logger->set_pattern("%d/%m/%Y %H:%M:%S.%e %L: %v");
  logger->set_level(spdlog::level::debug);

  return logger;
}

} // namespace

bool Log::initialize() noexcept
{
  m_logger = CreateConsoleLogger(m_channelName);

  return m_logger != nullptr;
}

} // namespace net
