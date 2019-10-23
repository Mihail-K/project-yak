#ifndef __LOGGER_H__
#define __LOGGER_H__

typedef enum {
    LOG_LEVEL_DEBUG = 0,
    LOG_LEVEL_INFO  = 1,
    LOG_LEVEL_WARN  = 2,
    LOG_LEVEL_ERROR = 3,
    LOG_LEVEL_FATAL = 4
} LogLevel;

#define debug(format, ...) \
    log(LOG_LEVEL_DEBUG, format, ## __VA_ARGS__)
#define info(format, ...)  \
    log(LOG_LEVEL_INFO, format, ## __VA_ARGS__)
#define warn(format, ...)  \
    log(LOG_LEVEL_WARN, format, ## __VA_ARGS__)
#define error(format, ...) \
    log(LOG_LEVEL_ERROR, format, ## __VA_ARGS__)
#define fatal(format, ...) \
    log(LOG_LEVEL_FATAL, format, ## __VA_ARGS__)

void log(LogLevel level, const char* format, ...);

#endif
