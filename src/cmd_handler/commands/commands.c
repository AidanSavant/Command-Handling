#include "commands.h"

void hi(Args args, const size_t e_argc) {
    CHECK_ARGS(args, e_argc)
    LOG_MSG(L_INFO, "Hello\n");
}

void add(Args args, const size_t e_argc) {
    CHECK_ARGS(args, e_argc)
    
    int lhs = (int) strtol(args_get(args, 0), NULL, 10),
        rhs = (int) strtol(args_get(args, 1), NULL, 10);

    LOG_MSG(L_INFO, "%d + %d = %d\n", lhs, rhs, lhs + rhs);
}

void mul(Args args, const size_t e_argc) {
    CHECK_ARGS(args, e_argc)
    
    int lhs = (int) strtol(args_get(args, 0), NULL, 10),
        rhs = (int) strtol(args_get(args, 1), NULL, 10);

    LOG_MSG(L_INFO, "%d * %d = %d\n", lhs, rhs, lhs * rhs);
}

