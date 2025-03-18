#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "../../utils/arg_parsing/arg_parsing.h"

/* == Utility function for validating args == */
#define CHECK_ARGS(args, e_argc)                                                                                  \
    do {                                                                                                          \
        size_t argc = args_len(args);                                                                             \
        if(args_len(args) != e_argc) {                                                                            \
            LOG_MSG(L_ERROR, "Invalid # of arguments! Expected %zu argument(s), but found %zu!\n", argc, e_argc); \
            return;                                                                                               \
        }                                                                                                         \
    } while(0);                                                                                                   \

/* == Command handlers example == */
void hi(Args, const size_t);
void add(Args, const size_t);
void mul(Args, const size_t);

#endif

