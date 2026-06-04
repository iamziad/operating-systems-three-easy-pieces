#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int pid = fork();

    switch (pid) {
    case -1: {
        char *msg = "fork(): something went wrong\n";
        write(STDERR_FILENO, msg, strlen(msg));
        exit(1);
    }
    case 0: {
        wait(NULL); // will fail and return -1
        char* msg = "child: hello dad\n";
        write(STDERR_FILENO, msg, strlen(msg));
        exit(0);
    }
    default:
        char *msg = "parent: hello son\n";
        write(STDERR_FILENO, msg, strlen(msg));
        break;
    }
    wait(NULL);
    return 0;
}
