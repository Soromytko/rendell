#include "logging.h"

namespace rendell {
RendellLogger::RendellLogger()
    : logr::Logger() {
}

const char *RendellLogger::getLevelName_Unsafe(logr::Level level) const {
    static const std::unordered_map<logr::Level, const char *> levelNames{
        {logr::Level::critical, "RENDELL::CRITICAL"}, {logr::Level::error, "RENDELL::ERROR"},
        {logr::Level::warning, "RENDELL::WARNING"},   {logr::Level::info, "RENDELL::INFO"},
        {logr::Level::debug, "RENDELL::DEBUG"},       {logr::Level::trace, "RENDELL::TRACE"},
    };

    auto it = levelNames.find(level);
    if (it != levelNames.end()) {
        return it->second;
    }

    return nullptr;
}

static std::unique_ptr<logr::Logger> s_logger{nullptr};

logr::Logger *get_logger() {
    if (!s_logger) {
        s_logger = std::make_unique<RendellLogger>();
    }

    return s_logger.get();
}

} // namespace rendell