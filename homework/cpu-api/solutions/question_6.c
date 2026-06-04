#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int pid = fork();

    switch (pid) {
    case -1:  {
        char *msg = "fork(): something went wrong\n";
        write(STDERR_FILENO, msg, strlen(msg));
        exit(1);
    }
    case 0: {
        char* msg = "child is working...\n";
        sleep(5);
        write(STDERR_FILENO, msg, strlen(msg));
        exit(1);
    }
    default:
        char *msg = "parent started\n";
        write(STDERR_FILENO, msg, strlen(msg));
        int status;
        waitpid(-1, &status, 0);
        if (WIFEXITED(status)) {
            printf("exit status: %d\n", WEXITSTATUS(status));
        }
        break;
    }
    return 0;
}
