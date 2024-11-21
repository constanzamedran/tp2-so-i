#include "../include/command.h"
#include "../include/exec.h"
#include "../include/jobs.h"
#include "../include/monitor.h"
#include "../include/pipes.h"

void change_directory(char* path)
{
    char* oldpwd = getenv("PWD");
    char newpwd[PATH];

    if (path == NULL || strcmp(path, "") == 0)
    {
        printf("Current directory: %s\n", oldpwd);
        return;
    }
    else if (strcmp(path, "-") == 0)
    {
        path = getenv("OLDPWD");
        if (path == NULL)
        {
            printf("OLDPWD not set.\n");
            return;
        }
    }

    if (chdir(path) != 0)
    {
        perror("cd");
    }
    else
    {
        getcwd(newpwd, sizeof(newpwd));
        setenv("OLDPWD", oldpwd, 1);
        setenv("PWD", newpwd, 1);
    }
}

void clear_shell()
{
    printf("\033[H\033[J");
}

void echo_message(char* message)
{
    if (message == NULL || strlen(message) == 0)
    {
        printf("\n");
        return;
    }

    if (message[0] == '$')
    {
        char* var = getenv(message + 1);
        if (var != NULL)
        {
            printf("%s\n", var);
        }
        else
        {
            printf("\n");
        }
    }
    else
    {
        printf("%s\n", message);
    }
}

void help()
{
    printf("\nAvailable commands:\n");
    printf("  cd <directory>     : Change the current directory to <directory>.\n");
    printf("                       : Use 'cd -' to go back to the previous directory.\n");
    printf("  clr                : Clear the terminal screen.\n");
    printf("  echo <message>     : Display <message> on the screen.\n");
    printf("                       : Supports environment variables (e.g., $VAR).\n");
    printf("  quit               : Exit the shell.\n");
    printf("\nUse these commands wisely and proceed with caution!\n");
}

void quit_shell()
{
    printf("Good bye :)\n");
    exit(0);
}

void list_commands()
{
    char input[BUFF_INPUT];
    // Read user input
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        perror("fgets");
        return;
    }

    // Delete the newline character
    input[strcspn(input, "\n")] = 0;

    // Check if input have &, indicates that commands have to exec in background
    int len = strlen(input);
    int is_background = 0;
    if (input[len - 1] == '&')
    {
        input[len - 1] = '\0'; // Remove '&'
        is_background = 1;
    }

    // Check if the input contains a pipe
    if (strstr(input, "|") != NULL)
    {
        execute_pipe_command(input);
    }
    else
    {
        // Handle single commands
        if (strncmp(input, "cd ", 3) == 0)
        {
            change_directory(input + 3);
        }
        else if (strcmp(input, "clr") == 0)
        {
            clear_shell();
        }
        else if (strncmp(input, "echo ", 5) == 0)
        {
            echo_message(input + 5);
        }
        else if (strcmp(input, "quit") == 0)
        {
            quit_shell();
        }
        else if (strcmp(input, "help") == 0)
        {
            help();
        }
        else if (strcmp(input, "mst") == 0)
        {
            start_monitor();
        }
        else if (strcmp(input, "msp") == 0)
        {
            stop_monitor();
        }
        else if (strcmp(input, "mss") == 0)
        {
            status_monitor();
        }
        else
        {
            if (is_background)
            {
                // Execute in background
                execute_background_process(input);
            }
            else
            {
                // Execute external command for non-built-in commands
                execute_external_command(input);
            }
        }
    }
}
