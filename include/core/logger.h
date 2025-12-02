#pragma once

#include <cstddef>
#include <memory>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace {
// Rotating file sink (5 MB per file, keep 3 files)
constexpr std::size_t LOG_FILE_SIZE = 5 * 1024 * 1024; // NOLINT
constexpr std::size_t LOG_FILE_COUNT = 3;

} // namespace

inline std::shared_ptr<spdlog::logger> &getLogger() {
  static auto logger = []() {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        "logs/opentetris.log", LOG_FILE_SIZE, LOG_FILE_COUNT);

    console_sink->set_level(spdlog::level::off);
    file_sink->set_level(spdlog::level::off);

    std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};

    auto log = std::make_shared<spdlog::logger>("OpenTetris", sinks.begin(),
                                                sinks.end());
    spdlog::register_logger(log);

    // Determine log level based on env variable, fallback to build type
    const char *env = std::getenv("LOG_LEVEL");
    spdlog::level::level_enum lvl;
#ifdef NDEBUG
    lvl = env ? spdlog::level::from_str(env) : spdlog::level::info;
#else
    lvl = env ? spdlog::level::from_str(env) : spdlog::level::debug;
#endif
    log->set_level(lvl);
    console_sink->set_level(lvl);
    file_sink->set_level(lvl);

    log->flush_on(spdlog::level::warn);
    return log;
  }();
  return logger;
}

#define LOG_TRACE(...) getLogger()->trace(__VA_ARGS__)
#define LOG_DEBUG(...) getLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...) getLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) getLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) getLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) getLogger()->critical(__VA_ARGS__)
