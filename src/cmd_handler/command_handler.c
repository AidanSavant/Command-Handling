/* == Command handler include == */
#include "command_handler.h"

/* == Command examples == */
#include "commands/commands.h"

/* == Basic hashing algorithm for strings == */
size_t calc_hash(const char *key) {
    size_t hash = 0xfefefefefe;

    while(*key++) {
        hash ^= *key;
        hash *= 0xaeaeaeae;
    }

    return hash;
}

/* == Default functions for hashmap init == */
void key_dtor(const char *_) { (void) _; }
void val_dtor(cmd_handler_fn _) { (void) _; }
bool is_equal(const char *l, const char *r) { return !strcmp(l, r); }
DEFINE_HASHMAP(CmdHandler, const char *, cmd_handler_fn, calc_hash, is_equal, key_dtor, val_dtor)

/* == Utility function wrapper == */
void exec_cmd(
    CmdHandler cmd_handler,
    const char *cmd,
    const char *args,
    const size_t e_argc
) {
    Args parsed_args = parse_args(args == NULL ? "" : args);

    cmd_handler_fn found_handler_fn = NULL;
    if(!CmdHandler_get(&cmd_handler, cmd, &found_handler_fn)) {
        LOG_MSG(L_ERROR, "%s is an invalid command!\n", cmd);
        return;
    }

    found_handler_fn(parsed_args, e_argc);

    delete_args(&parsed_args);
}

