# == Preferred compiler == #
CC = gcc

# == Source code files == #
SRC_FILES = main.c src/cmd_handler/command_handler.c src/cmd_handler/commands/commands.c src/utils/arg_parsing/arg_parsing.c

# == Optimized build == #
O_FLAGS = -Wall -Wextra -Wpedantic -Og -std=c2x -o
SRC_BIN = main

# == Debug build == #
DEBUG_FLAGS = -Wall -Wextra -Wpedantic -O0 -fsanitize=address,undefined -g3 -D DEBUG -std=c2x -o
DEBUG_BIN = main_debug

# Optimized build == #
build:
	$(CC) $(SRC_FILES) $(O_FLAGS) $(SRC_BIN)

build_debug:
	$(CC) $(SRC_FILES) $(DEBUG_FLAGS) $(DEBUG_BIN)

