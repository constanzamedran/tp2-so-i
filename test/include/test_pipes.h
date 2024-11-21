#include "unity.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/wait.h>

/**
 * @brief Prueba la ejecución de un solo comando.
 *
 * Esta función verifica que la función que ejecuta un solo comando 
 * funcione correctamente, comprobando que el comando se ejecute y 
 * devuelva el resultado esperado.
 */
void test_execute_single_command(void);

/**
 * @brief Prueba la ejecución de dos comandos conectados por un pipe.
 *
 * Esta función verifica que la función que maneja la ejecución de 
 * comandos encadenados a través de un pipe funcione correctamente.
 * Se espera que la salida del primer comando se pase como entrada 
 * al segundo comando y que el resultado sea el esperado.
 */
void test_execute_two_commands_with_pipe(void);

/**
 * @brief Prueba la ejecución de múltiples comandos conectados por pipes.
 *
 * Esta función verifica que la función que maneja la ejecución de 
 * múltiples comandos encadenados a través de pipes funcione correctamente.
 * Se asegura de que la salida de cada comando se pase correctamente 
 * al siguiente comando en la cadena.
 */
void test_execute_multiple_commands_with_pipe(void);

/**
 * @brief Prueba la ejecución de un comando inválido.
 *
 * Esta función verifica que la función que ejecuta comandos maneje 
 * adecuadamente los comandos inválidos, asegurándose de que se 
 * devuelva el código de error correcto y se manejen las situaciones 
 * de error apropiadamente.
 */
void test_execute_invalid_command(void);

/**
 * @brief Prueba la ejecución de un comando vacío.
 *
 * Esta función verifica que la función que ejecuta comandos maneje 
 * adecuadamente la entrada vacía, asegurándose de que no se produzcan 
 * errores y que el comportamiento sea el esperado cuando no se proporciona 
 * ningún comando para ejecutar.
 */
void test_execute_empty_command(void);
