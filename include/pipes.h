#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFF_INPUT 1024 // Buffer size for input commands.

/**
 * @brief Executes a series of commands connected by pipes.
 *
 * This function takes a string containing multiple commands separated by the pipe ('|') character,
 * creates pipes to connect the commands, and executes them in separate child processes.
 *
 * @param input A string containing the commands to execute, separated by '|'.
 *              For example: "ls -l | grep .c | wc -l"
 *
 * @note The function supports up to 10 commands in a single input string.
 * @note The buffer size for the input commands is defined by the macro BUFF_INPUT.
 */
void execute_pipe_command(char* input);
