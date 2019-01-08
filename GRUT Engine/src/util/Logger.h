#pragma once

#include "../DLLMacros.h"
#include "spdlog/spdlog.h"
#include <memory>

namespace GRUT {
  class Logger {
    friend class Root;
  private:
    static std::shared_ptr<spdlog::logger> s_logger;
    static void Initialize();
  public:
    static std::shared_ptr<spdlog::logger>& Instance() { return s_logger; }
  };
}

// Log macros
#define GRUT_DEBUG(...) ::GRUT::Logger::Instance()->debug(__VA_ARGS__)
#define GRUT_TRACE(...) ::GRUT::Logger::Instance()->trace(__VA_ARGS__)
#define GRUT_INFO(...)  ::GRUT::Logger::Instance()->info(__VA_ARGS__)
#define GRUT_WARN(...)  ::GRUT::Logger::Instance()->warn(__VA_ARGS__)
#define GRUT_ERROR(...) ::GRUT::Logger::Instance()->error(__VA_ARGS__)