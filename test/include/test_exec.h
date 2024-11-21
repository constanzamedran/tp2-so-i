#include "../../include/exec.h"
#include "unity.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @brief Establece el identificador de proceso en primer plano.
 *
 * Esta función se utiliza para establecer el PID (identificador de proceso) 
 * del proceso que debe ejecutarse en primer plano. Esto es útil para manejar 
 * la sincronización entre procesos y asegurarse de que el proceso 
 * en primer plano se controle correctamente.
 *
 * @param pid Identificador de proceso que se debe establecer como el 
 *            proceso en primer plano.
 */
void set_foreground_pid(pid_t pid);

/**
 * @brief Prueba la ejecución de un comando externo.
 *
 * Esta función verifica que el sistema pueda ejecutar un comando externo 
 * correctamente. Se espera que el comando se ejecute y que el sistema 
 * maneje adecuadamente la creación del proceso y la recolección del 
 * estado de salida del mismo.
 */
void test_execute_external_command(void);
