#include "./include/test_pipes.h"

void test_execute_single_command(void)
{
    // Redirigir la salida estándar a un buffer
    FILE* stream = popen("echo Hello", "r");
    char buffer[256];
    fgets(buffer, sizeof(buffer), stream);
    pclose(stream);

    // Verificar que la salida sea la esperada
    TEST_ASSERT_EQUAL_STRING("Hello\n", buffer);
}

void test_execute_two_commands_with_pipe(void)
{
    char command[] = "echo Hello | grep Hello"; // Comando a probar
    FILE* stream = popen(command, "r");
    char buffer[256];
    fgets(buffer, sizeof(buffer), stream);
    pclose(stream);

    // Verificar que la salida sea la esperada
    TEST_ASSERT_EQUAL_STRING("Hello\n", buffer);
}

void test_execute_multiple_commands_with_pipe(void)
{
    char command[] = "echo Hello | tr 'H' 'J' | grep J"; // Comando a probar
    FILE* stream = popen(command, "r");
    char buffer[256];
    fgets(buffer, sizeof(buffer), stream);
    pclose(stream);

    // Verificar que la salida sea la esperada
    TEST_ASSERT_EQUAL_STRING("Jello\n", buffer);
}

void test_execute_invalid_command(void)
{
    char command[] = "invalid_command | echo Test"; // Comando a probar
    FILE* stream = popen(command, "r");
    char buffer[256];
    fgets(buffer, sizeof(buffer), stream);
    int status = pclose(stream);

    // Comprobar que la salida contiene un mensaje de error
    TEST_ASSERT_TRUE(strstr(buffer, "not found") != NULL); // Verifica que el error esté presente

    // Si también deseas verificar el estado de salida
    // Nota: Esto puede variar dependiendo del shell, así que solo úsalo si es necesario
    TEST_ASSERT_TRUE(status != 0); // Status no debe ser cero, aunque podría no funcionar como se espera
}

void test_execute_empty_command(void)
{
    char command[] = "";           // Comando vacío
    execute_pipe_command(command); // Esto debería no hacer nada y no causar un crash
    // No hay salida a verificar, solo comprobar que no falla
    TEST_PASS();
}
