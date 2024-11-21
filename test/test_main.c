#include "./include/test_command.h"
#include "./include/test_exec.h"
#include "./include/test_jobs.h"
#include "./include/test_pipes.h"
#include "unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

int main(void)
{
    UNITY_BEGIN();

    // Ejecutar las pruebas
    RUN_TEST(test_change_directory_valid_path);
    RUN_TEST(test_clear_shell);
    RUN_TEST(test_echo_message_normal);
    RUN_TEST(test_echo_message_env_var);
    RUN_TEST(test_echo_message_empty);
    // RUN_TEST(test_quit_shell);
    RUN_TEST(test_execute_external_command);
    RUN_TEST(test_execute_background_process);
    RUN_TEST(test_execute_single_command);
    RUN_TEST(test_execute_two_commands_with_pipe);
    RUN_TEST(test_execute_multiple_commands_with_pipe);
    RUN_TEST(test_execute_empty_command);
    RUN_TEST(test_list_commands_change_directory);
    RUN_TEST(test_list_commands_clear_shell);
    RUN_TEST(test_list_commands_echo_message);
    RUN_TEST(test_list_commands_echo_message_env_var);
    RUN_TEST(test_list_commands_invalid_command);

    return UNITY_END();
}
