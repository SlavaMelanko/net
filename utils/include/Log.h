#pragma once

#include <spdlog/spdlog.h>

namespace net {

class Log
{
public:
  static void initialize() noexcept;

  template<typename... Args>
  static void error(std::string_view fmt, const Args&... args)
  {
    if (!m_initialized) return;
    spdlog::get(m_channel)->error(fmt, args...);
  }

  template<typename... Args>
  static void info(std::string_view fmt, const Args&... args)
  {
    if (!m_initialized) return;
    spdlog::get(m_channel)->info(fmt, args...);
  }

  template<typename... Args>
  static void warn(std::string_view fmt, const Args&... args)
  {
    if (!m_initialized) return;
    spdlog::get(m_channel)->warn(fmt, args...);
  }

private:
  static std::string m_channel;
  static std::atomic_bool m_initialized;
};

} // namespace net
