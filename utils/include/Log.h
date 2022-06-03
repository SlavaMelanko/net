#pragma once

#include <spdlog/spdlog.h>

namespace net {

class Log
{
public:
  static bool initialize() noexcept;

  template<typename... Args>
  static void error(std::string_view fmt, Args&&... args)
  {
    if (m_logger) {
      m_logger->error(fmt, std::forward<Args>(args)...);
    }
  }

  template<typename... Args>
  static void info(std::string_view fmt, Args&&... args)
  {
    if (m_logger) {
      m_logger->info(fmt, std::forward<Args>(args)...);
    }
  }

  template<typename... Args>
  static void warn(std::string_view fmt, Args&&... args)
  {
    if (m_logger) {
      m_logger->warn(fmt, std::forward<Args>(args)...);
    }
  }

private:
  static inline const std::string m_channelName{ "console" };
  static inline std::shared_ptr<spdlog::logger> m_logger;
};

} // namespace net
