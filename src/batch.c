#include "../include/batch.h"
#include "../include/exec.h"

void execute_command_from_file(FILE* file)
{
    char input[BUFF_INPUT];

    // Read and execute each line
    while (fgets(input, sizeof(input), file) != NULL)
    {
        // Delete step line
        input[strcspn(input, "\n")] = 0;

        // Check if command is "quit"
        if (strcmp(input, "quit") == 0)
        {
            printf("Good bye :)\n");
            exit(0);
        }
        else
        {
            execute_external_command(input); // Execute external commands
        }
    }
}
