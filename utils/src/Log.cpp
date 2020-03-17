#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace utils {

void InitLogging()
{
  spdlog::stdout_color_mt("stdout");
}

} // namespace utils
