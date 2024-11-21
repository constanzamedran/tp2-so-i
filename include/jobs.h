#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @brief Ejecuta un comando en segundo plano.
 *
 * Esta función crea un nuevo proceso en segundo plano que ejecuta el comando especificado.
 * En el proceso hijo, se utiliza `execvp` para ejecutar el comando y sus argumentos. El
 * proceso padre imprime el ID del trabajo y el ID del proceso del nuevo proceso en segundo
 * plano.
 *
 * @param command Comando a ejecutar, con los argumentos separados por espacios.
 */
void execute_background_process(char* command);