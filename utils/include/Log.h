#pragma once

#include <spdlog/spdlog.h>

namespace utils {

void InitLogging();

} // namespace utils

#define CRIT(...) spdlog::get("stdout")->critical(__VA_ARGS__);
#define DEBUG(...) spdlog::get("stdout")->debug(__VA_ARGS__);
#define ERROR(...) spdlog::get("stdout")->error(__VA_ARGS__);
#define INFO(...) spdlog::get("stdout")->info(__VA_ARGS__);
#define TRACE(...) spdlog::get("stdout")->trace(__VA_ARGS__);
#define WARN(...) spdlog::get("stdout")->warn(__VA_ARGS__);
