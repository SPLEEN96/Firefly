#pragma once

#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace Firefly {

class Logger {
  public:
    Logger();
    ~Logger();

    static void Init();

    static std::shared_ptr<spdlog::logger> GetCoreLogger() {
        return m_core_logger;
    }
    static std::shared_ptr<spdlog::logger> GetClientLogger() {
        return m_client_logger;
    }

  private:
    static std::shared_ptr<spdlog::logger> m_core_logger;
    static std::shared_ptr<spdlog::logger> m_client_logger;
};

} // namespace Firefly

#define FFLY_LOG_CORE_TRACE(...)                                               \
    Firefly::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define FFLY_LOG_CORE_INFO(...)                                                \
    Firefly::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define FFLY_LOG_CORE_WARN(...)                                                \
    Firefly::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define FFLY_LOG_CORE_ERROR(...)                                               \
    Firefly::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define FFLY_LOG_CORE_CRITICAL(...)                                            \
    Firefly::Logger::GetCoreLogger()->critical(__VA_ARGS__)

#define FFLY_LOG_APP_TRACE(...)                                                \
    Firefly::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define FFLY_LOG_APP_INFO(...)                                                 \
    Firefly::Logger::GetClientLogger()->info(__VA_ARGS__)
#define FFLY_LOG_APP_WARN(...)                                                 \
    Firefly::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define FFLY_LOG_APP_ERROR(...)                                                \
    Firefly::Logger::GetClientLogger()->error(__VA_ARGS__)
#define FFLY_LOG_APP_CRITICAL(...)                                             \
    Firefly::Logger::GetClientLogger()->critical(__VA_ARGS__)