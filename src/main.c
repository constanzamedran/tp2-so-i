#include "../include/batch.h"
#include "../include/command.h"
#include "../include/exec.h"
#include "../include/jobs.h"
#include "../include/monitor.h"
#include "../include/pipes.h"
#include "../include/prompt.h"
#include "../include/signals.h"

#define TRUE 1

int main(int argc, char* argv[])
{
    init_shell();
    setup_signals();

    const char* fifo_path = "/tmp/monitor_fifo";

    // Crear el FIFO si no existe
    if (mkfifo(fifo_path, 0666) == -1 && errno != EEXIST)
    {
        perror("Error al crear el FIFO");
        exit(EXIT_FAILURE);
    }

    // Verificar si se ha pasado un archivo como argumento
    if (argc > 1)
    {
        FILE* file = fopen(argv[1], "r");
        if (file == NULL)
        {
            perror("Error al abrir el archivo de comandos");
            return 1;
        }

        // Leer y ejecutar los comandos desde el archivo
        execute_command_from_file(file);
        fclose(file);
    }
    else
    {
        // Modo interactivo
        while (TRUE)
        {
            show_prompt();
            list_commands();
        }
    }
    unlink(fifo_path);

    return 0;
}
