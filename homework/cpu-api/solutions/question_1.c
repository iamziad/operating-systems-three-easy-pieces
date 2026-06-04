#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int x = 100;

    int pid = fork();

    switch (pid) {
    case -1:
        char* msg = "fork(): something went wrong\n";
        write(STDERR_FILENO, msg, strlen(msg));
        exit(1);

    case 0:
        x = 50;
        printf("child, x = %d\n", x);
        exit(0);

    default:
        x = 25;
        printf("parent, x = %d\n", x);
    }

    wait(NULL);
    return 0;
}
