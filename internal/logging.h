#pragma once
#include <format>
#include <logr/logr.h>

namespace rendell {
class RendellLogger final : public logr::Logger {
public:
    RendellLogger();
    ~RendellLogger() = default;

private:
    const char *getLevelName_Unsafe(logr::Level level) const override;
};

logr::Logger *get_logger();
} // namespace rendell

#define RENDELL_CRITICAL(formatStr, ...)                                                           \
    rendell::get_logger()->critical(std::format(formatStr, ##__VA_ARGS__))
#define RENDELL_ERROR(formatStr, ...)                                                              \
    rendell::get_logger()->error(std::format(formatStr, ##__VA_ARGS__))
#define RENDELL_WARNING(formatStr, ...)                                                            \
    rendell::get_logger()->warning(std::format(formatStr, ##__VA_ARGS__))
#define RENDELL_INFO(formatStr, ...)                                                               \
    rendell::get_logger()->info(std::format(formatStr, ##__VA_ARGS__))
#define RENDELL_DEBUG(formatStr, ...)                                                              \
    rendell::get_logger()->debug(std::format(formatStr, ##__VA_ARGS__))
#define RENDELL_TRACE(formatStr, ...)                                                              \
    rendell::get_logger()->trace(std::format(formatStr, ##__VA_ARGS__))
