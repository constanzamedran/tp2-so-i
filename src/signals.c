#include "../include/signals.h"

pid_t foreground_pid = 0;

void signal_handler(int signo)
{
    if (foreground_pid > 0)
    {
        // Enviar la señal al proceso en primer plano
        kill(foreground_pid, signo);
    }
}

void setup_signals()
{
    signal(SIGINT, signal_handler);  // Signal for interrupt (CTRL+C)
    signal(SIGTSTP, signal_handler); // Signal for stop (CTRL+Z)
    signal(SIGQUIT, signal_handler); // Signal for quit (CTRL+\)
}

void set_foreground_pid(pid_t pid)
{
    foreground_pid = pid;
}
