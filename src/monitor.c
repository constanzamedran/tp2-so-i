#include "../include/monitor.h"
#include "../include/signals.h"

static pid_t monitor_pid = -1;
static int monitoring = 0;

void start_monitor()
{
    if (monitor_pid == -1)
    {
        monitor_pid = fork();
        if (monitor_pid == 0)
        {
            // Proceso hijo: solo ejecuta el monitor
            int devnull = open("/dev/null", O_RDWR);
            if (devnull != -1)
            {
                dup2(devnull, STDOUT_FILENO); // Redirige stdout
                dup2(devnull, STDERR_FILENO); // Redirige stderr
                close(devnull);
            }

            execlp("../lib/monitoring_project/build/monitoring_project", "monitoring_project", NULL);
            perror("execlp failed");
            exit(EXIT_FAILURE);
        }
        else
        {
            monitoring = 1;
            printf("Start monitor.\n");
        }
    }
    else
    {
        printf("Monitor already in use.\n");
    }
}

void stop_monitor()
{
    if (monitor_pid != -1)
    {
        kill(monitor_pid, SIGTERM);
        waitpid(monitor_pid, NULL, 0);
        monitor_pid = -1;
        monitoring = 0;
        printf("Monitor stopped.\n");
    }
    else
    {
        printf("No monitor executing.\n");
    }
}

void status_monitor()
{
    const char* fifo_path = "/tmp/monitor_fifo";
    int option = 0;

    printf("Monitoreo en ejecución (PID: %d).\n\n", getpid());

    // Menú interactivo
    printf("Selecciona la métrica que deseas ver:\n");
    printf("    1. Uso de CPU\n");
    printf("    2. Uso de Memoria\n");
    printf("    3. Uso de Disco\n");
    printf("    4. Uso de Red\n");
    printf("    5. Número de Procesos\n");
    printf("    6. Interrupciones de Contexto\n");
    printf("    7. Todas las métricas\n");
    printf("    Selecciona una opción (1-7): ");
    scanf("%d", &option);
    printf("    \n ");

    // Abrir el FIFO en modo de solo lectura
    int fifo_fd = open(fifo_path, O_RDONLY);
    if (fifo_fd == -1)
    {
        perror("Error al abrir el FIFO");
        return;
    }

    // Intentar leer datos solo una vez
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer)); // Limpiar el buffer

    ssize_t bytes_read = read(fifo_fd, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0)
    {
        buffer[bytes_read] = '\0'; // Asegurar que el buffer sea una cadena válida

        // Analizar el JSON recibido
        cJSON* json = cJSON_Parse(buffer);
        if (json)
        {
            // Obtener los valores de las métricas
            cJSON* cpu_usage = cJSON_GetObjectItem(json, "cpu_usage");
            cJSON* memory_usage = cJSON_GetObjectItem(json, "memory_usage");
            cJSON* disk_usage = cJSON_GetObjectItem(json, "disk_usage");
            cJSON* network_usage = cJSON_GetObjectItem(json, "network_usage");
            cJSON* process_count = cJSON_GetObjectItem(json, "process_count");
            cJSON* context_switches = cJSON_GetObjectItem(json, "context_switches");

            // Mostrar valores según la opción seleccionada
            if (option == 1 && cpu_usage && cpu_usage->valuedouble != 0)
            {
                printf("Uso de CPU: %.2f%%\n\n", cpu_usage->valuedouble);
            }
            if (option == 2 && memory_usage && memory_usage->valuedouble != 0)
            {
                printf("Uso de Memoria: %.2f MB\n\n", memory_usage->valuedouble);
            }
            if (option == 3 && disk_usage && disk_usage->valuedouble != 0)
            {
                printf("Uso de Disco: %.2f GB\n\n", disk_usage->valuedouble);
            }
            if (option == 4 && network_usage && network_usage->valuedouble != 0)
            {
                printf("Uso de Red: %.2f KB/s\n\n", network_usage->valuedouble);
            }
            if (option == 5 && process_count && process_count->valueint != 0)
            {
                printf("Número de Procesos: %d\n\n", process_count->valueint);
            }
            if (option == 6 && context_switches && context_switches->valuedouble != 0)
            {
                printf("Interrupciones de Contexto: %.2f\n\n", context_switches->valuedouble);
            }
            if (option == 7)
            { // Mostrar todas las métricas
                if (cpu_usage && cpu_usage->valuedouble != 0)
                {
                    printf("Uso de CPU: %.2f%%\n", cpu_usage->valuedouble);
                }
                if (memory_usage && memory_usage->valuedouble != 0)
                {
                    printf("Uso de Memoria: %.2f MB\n", memory_usage->valuedouble);
                }
                if (disk_usage && disk_usage->valuedouble != 0)
                {
                    printf("Uso de Disco: %.2f GB\n", disk_usage->valuedouble);
                }
                if (network_usage && network_usage->valuedouble != 0)
                {
                    printf("Uso de Red: %.2f KB/s\n", network_usage->valuedouble);
                }
                if (process_count && process_count->valueint != 0)
                {
                    printf("Número de Procesos: %d\n", process_count->valueint);
                }
                if (context_switches && context_switches->valuedouble != 0)
                {
                    printf("Interrupciones de Contexto: %.2f\n\n", context_switches->valuedouble);
                }
            }

            // Liberar el objeto JSON
            cJSON_Delete(json);
        }
        else
        {
            fprintf(stderr, "Error al analizar el JSON: %s\n", cJSON_GetErrorPtr());
        }
    }
    else if (bytes_read == 0)
    {
        // En caso de que no haya datos en el FIFO, mostrar el mensaje solo una vez
        printf("No se recibieron datos en el FIFO.\n");
    }
    else if (bytes_read == -1)
    {
        perror("Error al leer del FIFO");
    }

    close(fifo_fd);
}
