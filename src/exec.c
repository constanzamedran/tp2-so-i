#include "../include/exec.h"
#include "../include/signals.h"

void execute_external_command(char* input)
{
    // Dividir la entrada en argumentos
    char* args[BUFF_INPUT / 2 + 1]; // Array para los argumentos del programa
    int i = 0;

    // Usar strtok para dividir la cadena en argumentos
    char* token = strtok(input, " ");
    while (token != NULL && i < BUFF_INPUT / 2)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL; // Terminar la lista de argumentos con NULL

    // Crear un proceso hijo
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("Error al crear el proceso hijo");
    }
    else if (pid == 0)
    {
        // Código del proceso hijo
        if (execvp(args[0], args) == -1)
        {
            perror("Error al ejecutar el comando");
        }
        exit(EXIT_FAILURE); // Terminar el proceso hijo si execvp falla
    }
    else
    {
        set_foreground_pid(pid);
        int status;
        waitpid(pid, &status, 0); // Esperar a que el hijo termine
        if (WIFEXITED(status))
        {
            // Comprobar si el proceso terminó con éxito o error
            if (WEXITSTATUS(status) != 0)
            {
                printf("El comando falló con código de salida %d\n", WEXITSTATUS(status));
            }
        }
    }
    set_foreground_pid(0);
}
