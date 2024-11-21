#include <ctype.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFF_INPUT 1024 // Buffer size for input commands.

/**
 * @brief Executes an external command.
 *
 * This function parses the input command, creates a child process,
 * and executes the command using execvp. It also handles background
 * execution of commands if specified by an '&' at the end of the input.
 *
 * @param input The command line input string to execute.
 */
void execute_external_command(char* input);
