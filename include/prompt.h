#include <limits.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define HOST_NAME 255 // Maximum size for hostname.
#define PATH 4096     // Maximum size for path.

/**
 * @brief Initializes the shell and displays a welcome message.
 *
 * This function prints a welcome message to the user, including
 * a warning about using the shell. It retrieves the username from
 * the environment and displays it.
 */
void init_shell();

/**
 * @brief Displays the shell prompt with user, hostname, and current directory.
 *
 * This function retrieves the current username, hostname, and
 * current working directory. It formats the prompt to display
 * the user's name, hostname, and the current directory,
 * replacing the home directory path with '~' for easier readability.
 */
void show_prompt();
