#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFF_INPUT 1024 // Buffer size for input commands.

/**
 * @brief Executes a command with input and output redirection.
 *
 * This function takes a string containing a command and redirects its input and/or output
 * to/from specified files. The command may include '<' for input redirection and '>' for
 * output redirection.
 *
 * @param input A string containing the command with potential redirection.
 *              For example: "grep 'error' < input.txt > output.txt"
 *
 * @note The function supports only one input and one output redirection at a time.
 * @note The buffer size for the input commands is defined by the macro BUFF_INPUT.
 */
void execute_redirection_command(char* input);
