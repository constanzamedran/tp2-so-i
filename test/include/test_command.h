#include "../../include/command.h"
#include "unity.h"
#include <string.h>
#include <unistd.h>

/**
 * @brief Prueba para verificar el cambio de directorio con una ruta válida.
 * 
 * Esta función prueba que el comando de cambio de directorio se ejecute correctamente
 * cuando se proporciona una ruta válida.
 */
void test_change_directory_valid_path(void);

/**
 * @brief Prueba para verificar la limpieza del shell.
 * 
 * Esta función prueba que el comando de limpieza del shell se ejecute correctamente,
 * asegurándose de que se limpien adecuadamente los comandos y la salida en el shell.
 */
void test_clear_shell(void);

/**
 * @brief Prueba para verificar el funcionamiento del comando echo con un mensaje normal.
 * 
 * Esta función prueba que el comando echo imprima correctamente un mensaje normal en
 * la salida estándar.
 */
void test_echo_message_normal(void);

/**
 * @brief Prueba para verificar el funcionamiento del comando echo con una variable de entorno.
 * 
 * Esta función prueba que el comando echo pueda imprimir correctamente el valor de
 * una variable de entorno.
 */
void test_echo_message_env_var(void);

/**
 * @brief Prueba para verificar el funcionamiento del comando echo con un mensaje vacío.
 * 
 * Esta función prueba que el comando echo maneje correctamente el caso de un mensaje
 * vacío, asegurándose de que no se produzca ningún error.
 */
void test_echo_message_empty(void);

/**
 * @brief Prueba para verificar el comportamiento del comando quit en el shell.
 * 
 * Esta función prueba que el comando quit se ejecute correctamente y cierre el shell
 * sin errores.
 */
void test_quit_shell(void);

/**
 * @brief Prueba para verificar el manejo de un comando inválido en la lista de comandos.
 * 
 * Esta función prueba que el shell maneje adecuadamente un comando inválido, mostrando
 * el mensaje de error correspondiente.
 */
void test_list_commands_invalid_command(void);

/**
 * @brief Prueba para verificar la ejecución del comando quit desde la lista de comandos.
 * 
 * Esta función prueba que al seleccionar el comando quit desde la lista de comandos,
 * el shell se cierre correctamente.
 */
void test_list_commands_quit_shell(void);

/**
 * @brief Prueba para verificar el funcionamiento del comando echo desde la lista de comandos
 * con una variable de entorno.
 * 
 * Esta función prueba que al ejecutar el comando echo desde la lista de comandos con
 * una variable de entorno, se imprima el valor correspondiente sin errores.
 */
void test_list_commands_echo_message_env_var(void);

/**
 * @brief Prueba para verificar el funcionamiento del comando echo desde la lista de comandos
 * con un mensaje normal.
 * 
 * Esta función prueba que al ejecutar el comando echo desde la lista de comandos con
 * un mensaje normal, se imprima correctamente en la salida estándar.
 */
void test_list_commands_echo_message(void);

/**
 * @brief Prueba para verificar la ejecución del comando clear desde la lista de comandos.
 * 
 * Esta función prueba que al seleccionar el comando clear desde la lista de comandos,
 * el shell se limpie adecuadamente.
 */
void test_list_commands_clear_shell(void);

/**
 * @brief Prueba para verificar el funcionamiento del comando change directory desde la lista de comandos.
 * 
 * Esta función prueba que al seleccionar el comando change directory desde la lista de comandos,
 * el directorio cambie correctamente si se proporciona una ruta válida.
 */
void test_list_commands_change_directory(void);
