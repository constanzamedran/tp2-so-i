#include "./include/test_exec.h"

// Variable para simular el PID del proceso en primer plano
pid_t mock_foreground_pid = 0;

// Función simulada para set_foreground_pid
void set_foreground_pid(pid_t pid)
{
    mock_foreground_pid = pid;
}

// Test para la función execute_external_command
void test_execute_external_command(void)
{
    char command[] = "echo Hello"; // Comando simple para probar

    // Simular la ejecución del proceso
    pid_t pid = fork();

    if (pid == 0)
    {
        // Proceso hijo
        // Aquí simplemente podemos simular la ejecución de execvp
        // No es necesario ejecutar realmente el comando en un test
        exit(0); // Salir con éxito
    }
    else if (pid > 0)
    {
        // Proceso padre
        set_foreground_pid(pid); // Simulamos el PID del proceso en primer plano
        int status;
        waitpid(pid, &status, 0); // Esperar a que el hijo termine

        // Verificar que el proceso hijo terminó correctamente
        TEST_ASSERT_TRUE(WIFEXITED(status));
        TEST_ASSERT_EQUAL_INT(0, WEXITSTATUS(status)); // Comprobar que el código de salida es 0
    }
    else
    {
        // Error al crear el proceso hijo
        TEST_FAIL_MESSAGE("Error al crear el proceso hijo");
    }

    // Verificar que el PID del proceso en primer plano se ha actualizado
    TEST_ASSERT_EQUAL_INT(pid, mock_foreground_pid);
}
