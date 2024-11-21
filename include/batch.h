#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFF_INPUT 1024 // Buffer size for input commands.

/**
 * @brief Executes commands read from a file.
 *
 * This function reads lines from a given file and executes each line
 * as a command. It handles the "quit" command to exit the program.
 *
 * @param file Pointer to the file from which commands are read.
 */
void execute_command_from_file(FILE* file);