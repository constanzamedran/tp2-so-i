#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PATH 4096       // Maximum path length.
#define BUFF_INPUT 1024 // Buffer size for user input.

/**
 * @brief Changes the current working directory.
 *
 * This function changes the directory to the specified path.
 * If the path is "-" it switches to the previous directory stored in `OLDPWD`.
 * If the path is NULL or empty, it displays the current directory.
 *
 * @param path Directory path to change to. If NULL or empty, shows current directory.
 */
void change_directory(char* path);

/**
 * @brief Clears the terminal screen.
 *
 * Uses ANSI escape codes to clear the screen and reset the cursor position.
 */
void clear_shell();

/**
 * @brief Outputs a message to the terminal.
 *
 * Prints the provided message to the terminal. If the message starts with `$`,
 * it attempts to print the value of the corresponding environment variable.
 *
 * @param message The message to display. If it starts with `$`, prints environment variable value.
 */
void echo_message(char* message);

/**
 * @brief Displays a help message with available commands.
 *
 * Lists each built-in command and a brief description of its usage.
 */
void help();

/**
 * @brief Exits the shell application.
 *
 * Displays a farewell message before terminating the program.
 */
void quit_shell();

/**
 * @brief Reads and executes commands from user input.
 *
 * Processes commands entered by the user and executes the appropriate function.
 * Supports built-in commands as well as external command execution.
 */
void list_commands();
