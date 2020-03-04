#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

void InitLogging()
{
    spdlog::stdout_color_mt("stdout");
}
