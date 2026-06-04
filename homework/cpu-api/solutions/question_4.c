#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *msg = "parent: executing ls\n";
    write(STDOUT_FILENO, msg, strlen(msg));
    int pid = fork();

    switch (pid) {
    case -1: {
        char *msg = "fork(): something went wrong\n";
        write(STDERR_FILENO, msg, strlen(msg));
        exit(1);
    }
    case 0: {
        char *args[] = {"ls", "-l", "-a", NULL};
        execv("/bin/ls", args);
        char *msg = "execv(): something went wrong\n";
        write(STDERR_FILENO, msg, strlen(msg));
        exit(1);
    }
    default:
        wait(NULL);
        char *msg = "parent finished\n";
        write(STDOUT_FILENO, msg, strlen(msg));
        break;
    }

    return 0;
}
