#include "../include/jobs.h"

volatile int job_id = 1;

void execute_background_process(char* command)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Error al crear el proceso hijo");
    }
    else if (pid == 0)
    {
        // Proceso hijo ejecuta el comando
        // Dividimos el comando en argumentos
        char* args[100];
        int i = 0;
        char* token = strtok(command, " ");
        while (token != NULL && i < 100)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Ejecutar el comando
        if (execvp(args[0], args) == -1)
        {
            perror("Error al ejecutar el comando");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        // Proceso padre imprime el ID de trabajo y el ID de proceso
        printf("[%d] %d\n", job_id++, pid);
        wait(NULL);
    }
}
