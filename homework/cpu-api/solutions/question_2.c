#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int fd = open("./file.txt", O_CREAT | O_RDWR, 0666);

    int pid = fork();

    switch (pid) {
    case -1: {
        char *msg = "fork(): something wentwrong\n";
        write(STDERR_FILENO, msg, strlen(msg));
        exit(1);
    }
    case 0: {
        char *msg = "child wrote this line\n";
        write(fd, msg, strlen(msg));
        exit(0);
    }
    default:
        char *msg = "parent wrote this line\n";
        write(fd, msg, strlen(msg));
    }

    wait(NULL);
    return 0;
}
