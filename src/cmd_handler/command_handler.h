#ifndef CMD_HANDLER_H_
#define CMD_HANDLER_H_

/* == Std includes == */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* == Logger include == */
#include "../utils/logger/logger.h"

/* == Generic container include(s) == */
#include "../utils/containers/hashmap.h"

/* == Arg parsing include == */
#include "../utils/arg_parsing/arg_parsing.h"

/* == Command handler examples == */
#include "commands/commands.h"

/* == Command handler type declarations == */
typedef void (*cmd_handler_fn)(const Args, const size_t);
DECL_HASHMAP(CmdHandler, const char *, cmd_handler_fn)

/* == Utility function == */
void exec_cmd(CmdHandler, const char *, const char *, const size_t);

#endif

