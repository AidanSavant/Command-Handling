#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdio.h>
#include <stdlib.h>

#define CLR "\x1b[0m"
#define BLU "\x1b[0;34m"
#define RED "\x1b[0;31m"
#define YEL "\x1b[0;33m"

typedef enum { L_INFO, L_DEBUG, L_ERROR, } log_level_t;

#define LOG_MSG(level, msg, ...) \
    do { \
        switch(level) { \
            case L_INFO:  fprintf(stdout, "[%sINFO%s] %s() %s:%d  | ", BLU, CLR, __func__, __FILE__, __LINE__); break; \
            case L_DEBUG: fprintf(stdout, "[%sDEBUG%s] %s() %s:%d | ", YEL, CLR, __func__, __FILE__, __LINE__); break; \
            case L_ERROR: fprintf(stderr, "[%sERROR%s] %s() %s:%d | ", RED, CLR, __func__, __FILE__, __LINE__); break; \
            default: fprintf(stderr, "Invalid logging level! Level: %d\n", level); exit(EXIT_FAILURE); \
        } \
        printf(msg, ##__VA_ARGS__); \
    } while(0) \

#endif

