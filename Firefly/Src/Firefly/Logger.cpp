#include "Logger.h"

namespace Firefly {

std::shared_ptr<spdlog::logger> Logger::m_core_logger;
std::shared_ptr<spdlog::logger> Logger::m_client_logger;

Logger::Logger() {}
Logger::~Logger() {}

void Logger::Init() {
    spdlog::set_pattern("%^[%T] %n: %v%$"); /* Timestamp Name : Message */

    m_core_logger = spdlog::stdout_color_mt("FIREFLY");
    m_core_logger->set_level(spdlog::level::level_enum::trace);

    m_client_logger = spdlog::stdout_color_mt("APPLICATION");
    m_client_logger->set_level(spdlog::level::level_enum::trace);
}

}  // namespace Firefly