#pragma once

#include <spdlog/spdlog.h>

namespace utils {

void InitLogging();

class Log
{
public:
  static void initialize();

  template<typename... Args>
  static void error(std::string_view fmt, const Args&... args)
  {
    if (!m_initialized)
      return;
    spdlog::get(m_channel)->error(fmt, args...);
  }

  template<typename... Args>
  static void info(std::string_view fmt, const Args&... args)
  {
    if (!m_initialized)
      return;
    spdlog::get(m_channel)->info(fmt, args...);
  }

  template<typename... Args>
  static void warn(std::string_view fmt, const Args&... args)
  {
    if (!m_initialized)
      return;
    spdlog::get(m_channel)->warn(fmt, args...);
  }

private:
  static std::string m_channel;
  static std::atomic_bool m_initialized;
};

} // namespace utils

#define CRIT(...) spdlog::get("stdout")->critical(__VA_ARGS__);
#define DEBUG(...) spdlog::get("stdout")->debug(__VA_ARGS__);
#define ERROR(...) spdlog::get("stdout")->error(__VA_ARGS__);
#define INFO(...) spdlog::get("stdout")->info(__VA_ARGS__);
#define TRACE(...) spdlog::get("stdout")->trace(__VA_ARGS__);
#define WARN(...) spdlog::get("stdout")->warn(__VA_ARGS__);
