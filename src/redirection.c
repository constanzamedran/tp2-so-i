#include "../include/redirection.h"

void execute_redirection_command(char* input)
{
    char* command = strtok(input, "<>"); // Dividir el comando de la redirección
    char* input_file = NULL;
    char* output_file = NULL;

    // Buscar archivos de redirección
    while (1)
    {
        char* token = strtok(NULL, " ");
        if (token == NULL)
            break;

        if (strcmp(token, "<") == 0)
        {
            input_file = strtok(NULL, " ");
        }
        else if (strcmp(token, ">") == 0)
        {
            output_file = strtok(NULL, " ");
        }
    }

    // Crear un proceso hijo
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("Error al crear el proceso hijo");
        return;
    }
    else if (pid == 0)
    {
        // Redirigir entrada
        if (input_file)
        {
            int fd_in = open(input_file, O_RDONLY);
            if (fd_in < 0)
            {
                perror("Error al abrir el archivo de entrada");
                exit(EXIT_FAILURE);
            }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }

        // Redirigir salida
        if (output_file)
        {
            int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out < 0)
            {
                perror("Error al abrir el archivo de salida");
                exit(EXIT_FAILURE);
            }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }

        // Dividir el comando en argumentos
        char* args[BUFF_INPUT / 2 + 1];
        int i = 0;
        char* cmd_token = strtok(command, " ");
        while (cmd_token != NULL)
        {
            args[i++] = cmd_token;
            cmd_token = strtok(NULL, " ");
        }
        args[i] = NULL; // Terminar la lista de argumentos con NULL

        // Ejecutar el comando
        execvp(args[0], args);
        perror("Error al ejecutar el comando");
        exit(EXIT_FAILURE); // Terminar el proceso hijo si execvp falla
    }
    else
    {
        // Código del proceso padre
        wait(NULL); // Esperar a que el hijo termine
    }
}
