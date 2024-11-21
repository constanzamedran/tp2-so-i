#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @brief Maneja las señales enviadas al proceso en primer plano.
 *
 * Esta función envía la señal especificada al proceso que se encuentra
 * en primer plano. Se utiliza para propagar señales como SIGINT, SIGTSTP y
 * SIGQUIT desde el terminal al proceso hijo.
 *
 * @param signo El número de la señal que se está manejando.
 */
void signal_handler(int signo);

/**
 * @brief Configura el manejo de señales para el proceso.
 *
 * Esta función asigna el manejador de señales `signal_handler` a las señales
 * SIGINT, SIGTSTP y SIGQUIT. Esto permite que el proceso reaccione a estas
 * señales, permitiendo el manejo adecuado de interrupciones y paradas.
 */
void setup_signals();

/**
 * @brief Establece el PID del proceso en primer plano.
 *
 * Esta función almacena el PID del proceso que debe recibir las señales.
 * Es importante para asegurar que las señales se envíen al proceso correcto.
 *
 * @param pid El PID del proceso en primer plano.
 */
void set_foreground_pid(pid_t pid);
