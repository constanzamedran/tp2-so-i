#include "../../include/jobs.h"
#include "unity.h"
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @brief Prueba la ejecución de un proceso en segundo plano.
 *
 * Esta función verifica que el sistema pueda ejecutar un proceso 
 * en segundo plano correctamente. Se espera que el proceso se inicie 
 * y que el control regrese al shell o al entorno de ejecución sin 
 * esperar a que el proceso en segundo plano termine.
 */
void test_execute_background_process(void);
