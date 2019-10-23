#include <stdarg.h>
#include <stdbool.h>

#include "logger.h"
#include "kprintf.h"

static inline bool _log_level_enabled(LogLevel level)
{
    #ifndef LOG_LEVEL
    #define LOG_LEVEL 0
    #endif

    return level >= LOG_LEVEL;
}

static inline const char* _log_level_label(LogLevel level)
{
    switch (level)
    {
        case LOG_LEVEL_DEBUG:
            return "DEBUG";

        case LOG_LEVEL_INFO:
            return " INFO";

        case LOG_LEVEL_WARN:
            return " WARN";

        case LOG_LEVEL_ERROR:
            return "ERROR";

        case LOG_LEVEL_FATAL:
            return "FATAL";

        default:
            return " NONE";
    }
}

void log(LogLevel level, const char* format, ...)
{
    va_list args;
    va_start(args, format);

    if (_log_level_enabled(level))
    {
        kprintf("[%s] ", _log_level_label(level));
        kvprintf(format, args);
    }

    va_end(args);
}
