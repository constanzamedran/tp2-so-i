#include "../include/prompt.h"

void init_shell()
{
    printf("\n\n");
    printf("*******************************\n");
    printf("**        WELCOME TO         **\n");
    printf("**         DYSTOPIA          **\n");
    printf("*******************************\n");
    printf("\n\n");

    printf("   - USE AT YOUR OWN RISK -\n");
    printf("   - Proceed with caution -\n");
    printf("\n");

    char* username = getenv("USER");
    if (username == NULL)
    {
        username = "UNKNOWN_USER";
    }
    printf("   USER: %s\n", username);

    printf("\n");
    sleep(1);
}

void show_prompt()
{
    char hostname[HOST_NAME];
    char cwd[PATH];
    char* user;

    // Get username
    user = getpwuid(getuid())->pw_name;

    // Get hostname
    gethostname(hostname, sizeof(hostname));

    // Get directory
    getcwd(cwd, sizeof(cwd));

    // Change home directory by ~
    char* home = getenv("HOME");
    if (home != NULL && strstr(cwd, home) == cwd)
    {
        char display_cwd[PATH];
        snprintf(display_cwd, sizeof(display_cwd), "~%s", cwd + strlen(home));
        printf("%s@%s:%s$", user, hostname, display_cwd);
    }
    else
    {
        printf("%s@%s:%s$", user, hostname, cwd);
    }
}
