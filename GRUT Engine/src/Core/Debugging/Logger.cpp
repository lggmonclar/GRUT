#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace GRUT {
    std::shared_ptr<spdlog::logger> Logger::s_logger;

    void Logger::Initialize() {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        s_logger = spdlog::stdout_color_mt("GRUT");
        s_logger->set_level(spdlog::level::trace);
    }
}
