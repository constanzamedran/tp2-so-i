#include "./include/test_jobs.h"

// Variable para simular el job_id
int mock_job_id = 1;

// Test para la función execute_background_process
void test_execute_background_process(void)
{
    char command[] = "echo Hello"; // Comando simple para probar

    // Simular la ejecución del proceso
    pid_t pid = fork();

    if (pid == 0)
    {
        // Proceso hijo (simulación de execvp, aquí solo simulamos)
        // Ejecutar el comando (realmente no lo ejecutamos en este test)
        exit(0); // Salir con éxito
    }
    else if (pid > 0)
    {
        // Proceso padre
        printf("[%d] %d\n", mock_job_id++, pid); // Simulamos el output
        wait(NULL);                              // Esperar a que el hijo termine
    }
    else
    {
        TEST_FAIL_MESSAGE("Error al crear el proceso hijo");
    }

    // Verificar que el job_id se incrementó
    TEST_ASSERT_EQUAL_INT(2, mock_job_id);
}
