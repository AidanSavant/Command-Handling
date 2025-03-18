#ifndef STRSPLIT_H_
#define STRSPLIT_H_

/* == Std include(s) == */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/cdefs.h>

/* == Generic container include(s) == */
#include "../containers/vector.h"

/* == Logger include == */
#include "../logger/logger.h"

/* == Container type declarations == */
DECL_VEC(char, Chars)
DECL_VEC(Chars, Args)

/* == Public interface == */
Args parse_args(const char *);
void delete_args(Args *);

char *args_get(const Args, const size_t);

size_t args_len(const Args);

/* == Private interface == */
void die(const char *);
void reset_chars(Chars *);

#endif

