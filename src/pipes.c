#include "../include/pipes.h"

void execute_pipe_command(char* input)
{
    char* commands[10]; // Soportamos hasta 10 comandos encadenados
    int num_commands = 0;
    char* token = strtok(input, "|");

    // Dividir la entrada en comandos separados por '|'
    while (token != NULL && num_commands < 10)
    {
        commands[num_commands++] = token;
        token = strtok(NULL, "|");
    }

    // Crear pipes
    int pipefd[2 * (num_commands - 1)];
    for (int i = 0; i < num_commands - 1; i++)
    {
        if (pipe(pipefd + i * 2) < 0)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    // Ejecutar cada comando
    for (int i = 0; i < num_commands; i++)
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            // Si no es el último comando, redirigir la salida
            if (i < num_commands - 1)
            {
                dup2(pipefd[i * 2 + 1], STDOUT_FILENO);
            }
            // Si no es el primer comando, redirigir la entrada
            if (i > 0)
            {
                dup2(pipefd[(i - 1) * 2], STDIN_FILENO);
            }

            // Cerrar los pipes en el proceso hijo
            for (int j = 0; j < 2 * (num_commands - 1); j++)
            {
                close(pipefd[j]);
            }

            // Dividir el comando actual en argumentos
            char* args[BUFF_INPUT / 2 + 1]; // Array para los argumentos del programa
            int j = 0;
            char* cmd_token = strtok(commands[i], " ");
            while (cmd_token != NULL)
            {
                args[j++] = cmd_token;
                cmd_token = strtok(NULL, " ");
            }
            args[j] = NULL; // Terminar la lista de argumentos con NULL

            // Ejecutar el comando
            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }

    // Cerrar los pipes en el proceso padre
    for (int i = 0; i < 2 * (num_commands - 1); i++)
    {
        close(pipefd[i]);
    }

    // Esperar a que todos los procesos hijos terminen
    for (int i = 0; i < num_commands; i++)
    {
        wait(NULL);
    }
}
