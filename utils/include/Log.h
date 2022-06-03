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
    if (auto logger = get(); logger) {
      logger->error(fmt, std::forward<Args>(args)...);
    }
  }

  template<typename... Args>
  static void info(std::string_view fmt, Args&&... args)
  {
    if (auto logger = get(); logger) {
      logger->info(fmt, std::forward<Args>(args)...);
    }
  }

  template<typename... Args>
  static void warn(std::string_view fmt, Args&&... args)
  {
    if (auto logger = get(); logger) {
      logger->warn(fmt, std::forward<Args>(args)...);
    }
  }

private:
  static std::shared_ptr<spdlog::logger> get();

  static std::string m_channelName;
};

} // namespace net
