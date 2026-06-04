#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

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
        char *msg = "hello";
        printf("%s\n", msg);
        exit(0);
    }
    default:
        wait(NULL);
        char *msg = "goodbye";
        printf("%s\n", msg);
    }
return 0;
}
