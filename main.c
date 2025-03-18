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

