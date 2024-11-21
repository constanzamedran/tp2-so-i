#include "./include/test_command.h"

void test_change_directory_valid_path(void)
{
    // Cambia a un directorio válido
    change_directory("/tmp");
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    TEST_ASSERT_EQUAL_STRING(cwd, "/tmp");
}

// Test para clear_shell
void test_clear_shell(void)
{
    // Llamar a clear_shell y verificar que no cause errores
    clear_shell();
    // No hay salida a verificar, solo comprobar que no falla
    TEST_PASS();
}

// Test para echo_message con mensaje normal
void test_echo_message_normal(void)
{
    // Llamar a echo_message y verificar que no cause errores
    echo_message("Hello, World!");
    // No hay salida a verificar, solo comprobar que no falla
    TEST_PASS();
}

// Test para echo_message con variable de entorno
void test_echo_message_env_var(void)
{
    setenv("TEST_VAR", "TestValue", 1); // Setear variable de entorno
    // Llamar a echo_message y verificar que no cause errores
    echo_message("$TEST_VAR");
    // No hay salida a verificar, solo comprobar que no falla
    TEST_PASS();
    unsetenv("TEST_VAR"); // Limpiar variable de entorno
}

// Test para echo_message sin mensaje
void test_echo_message_empty(void)
{
    // Llamar a echo_message y verificar que no cause errores
    echo_message("");
    // No hay salida a verificar, solo comprobar que no falla
    TEST_PASS();
}

// Prueba para quit_shell
void test_quit_shell(void)
{
    // Llamar a quit_shell y verificar que no cause errores
    quit_shell(); // Esto terminará el programa
    TEST_PASS();  // Si no se ha producido un error, la prueba pasa
}

void test_list_commands_change_directory(void)
{
    // Simular la entrada del usuario para cambiar al directorio /tmp
    char* input = "cd /tmp\n";
    FILE* stdin_backup = stdin;
    FILE* input_stream = fmemopen(input, strlen(input), "r");
    stdin = input_stream;

    // Llamar a la función
    list_commands();

    // Recuperar el directorio de trabajo actual
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));

    // Verificar que se haya cambiado al directorio correcto
    TEST_ASSERT_EQUAL_STRING(cwd, "/tmp");

    // Restaurar stdin
    stdin = stdin_backup;
    fclose(input_stream);
}

void test_list_commands_clear_shell(void)
{
    // Simular la entrada del usuario para clear_shell
    char* input = "clr\n";
    FILE* stdin_backup = stdin;
    FILE* input_stream = fmemopen(input, strlen(input), "r");
    stdin = input_stream;

    // Llamar a la función
    list_commands();

    // Verificar que no cause errores
    TEST_PASS();

    // Restaurar stdin
    stdin = stdin_backup;
    fclose(input_stream);
}

void test_list_commands_echo_message(void)
{
    // Simular la entrada del usuario para echo
    char* input = "echo Hello, World!\n";
    FILE* stdin_backup = stdin;
    FILE* input_stream = fmemopen(input, strlen(input), "r");
    stdin = input_stream;

    // Llamar a la función
    list_commands();

    // Verificar que no cause errores
    TEST_PASS();

    // Restaurar stdin
    stdin = stdin_backup;
    fclose(input_stream);
}

void test_list_commands_echo_message_env_var(void)
{
    setenv("TEST_VAR", "TestValue", 1); // Setear variable de entorno
    // Simular la entrada del usuario para echo de variable de entorno
    char* input = "echo $TEST_VAR\n";
    FILE* stdin_backup = stdin;
    FILE* input_stream = fmemopen(input, strlen(input), "r");
    stdin = input_stream;

    // Llamar a la función
    list_commands();

    // Verificar que no cause errores
    TEST_PASS();

    // Limpiar variable de entorno
    unsetenv("TEST_VAR");

    // Restaurar stdin
    stdin = stdin_backup;
    fclose(input_stream);
}

void test_list_commands_quit_shell(void)
{
    // Simular la entrada del usuario para quit_shell
    char* input = "quit\n";
    FILE* stdin_backup = stdin;
    FILE* input_stream = fmemopen(input, strlen(input), "r");
    stdin = input_stream;

    // Llamar a la función
    list_commands(); // Esto debería terminar el programa

    // Si no se produjo un error, la prueba pasa
    TEST_PASS();

    // Restaurar stdin
    stdin = stdin_backup;
    fclose(input_stream);
}

void test_list_commands_invalid_command(void)
{
    // Simular la entrada del usuario para un comando no válido
    char* input = "invalid_command\n";
    FILE* stdin_backup = stdin;
    FILE* input_stream = fmemopen(input, strlen(input), "r");
    stdin = input_stream;

    // Llamar a la función
    list_commands();

    // Aquí no puedes verificar la salida de un comando inválido, solo verificar que no cause errores
    TEST_PASS();

    // Restaurar stdin
    stdin = stdin_backup;
    fclose(input_stream);
}
