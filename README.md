# Command Handler Template
Basic command handling API in C.

# Example
```c
#include "src/cmd_handler/command_handler.h"
#include "src/utils/arg_parsing/arg_parsing.h"

int main(void) {
    CmdHandler cmd_handler = {0};
    if(!new_CmdHandler(&cmd_handler)) {
        LOG_MSG(L_ERROR, "Invalid command handler state!\n");
        return -1;
    }

    LOG_MSG(L_INFO, "Inserting command handlers!\n");

    CmdHandler_insert(&cmd_handler, "hi",  hi);
    CmdHandler_insert(&cmd_handler, "add", add);
    CmdHandler_insert(&cmd_handler, "mul", mul);

    LOG_MSG(L_INFO, "Command handlers inserted successfully!\n");

    exec_cmd(cmd_handler, "hi", NULL,    0);
    exec_cmd(cmd_handler, "add", "1 2",  2);
    exec_cmd(cmd_handler, "mul", "5 10", 2);

    exec_cmd(cmd_handler, "invalid cmd", NULL, -1);
    exec_cmd(cmd_handler, "add", "1", 2);

    destroy_CmdHandler(&cmd_handler);
}
```

# Main output
```bash
[INFO] main() main.c:11  | Inserting command handlers!
[INFO] main() main.c:17  | Command handlers inserted successfully!
[INFO] hi() src/cmd_handler/commands/commands.c:5  | Hello
[INFO] add() src/cmd_handler/commands/commands.c:14  | 1 + 2 = 3
[INFO] mul() src/cmd_handler/commands/commands.c:23  | 5 * 10 = 50
[ERROR] exec_cmd() src/cmd_handler/command_handler.c:36 | invalid cmd is an invalid command!
[ERROR] add() src/cmd_handler/commands/commands.c:9 | Invalid # of arguments! Expected 1 argument(s), but found 2!
```

# Explanation
The code uses a generic hashmap implementation to generate a type that maps a ``const char *`` to a ``cmd_handler_fn``, which is a type alias of ``void (*cmd_handler_fn)(...)``. We specify the key and value pair along with the expected amount of arguments for the command. 

If the expected amount of arguments doesn't equal the amount of arguments given, there is an error reported (but doesn't terminate or return anything, future code update). 

# TODO:
* Fix possible UAF bug & resolve memory leaks in relation to the bug.
* Rewrite the command handler type to return a ``bool`` or ``enum cmd_status`` enum type to indicate if the handler executed successfully or not.
