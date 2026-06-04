#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int pipefd[2];

    if (pipe(pipefd) < 0)
        perror("pipe()");

    pid_t pid1 = fork();

    if (pid1 < 0) {
        perror("fork()");
        exit(1);
    }

    if (pid1 == 0) {
        close(pipefd[0]);
        if (dup2(pipefd[1], STDOUT_FILENO) < 0) {
            perror("dup2()");
            exit(1);
        }
        close(pipefd[1]);
        char *msg = "message from child1";
        write(STDOUT_FILENO, msg, strlen(msg));
        exit(0);
    }

    pid_t pid2 = fork();

    if (pid2 < 0) {
        perror("fork()");
        exit(1);
    }

    if (pid2 == 0) {
        close(pipefd[1]);
        if (dup2(pipefd[0], STDIN_FILENO) < 0) {
            perror("dup2()");
            exit(1);
        }
        close(pipefd[0]);
        char buf[100];
        read(STDIN_FILENO, buf, sizeof(buf));
        printf("child2 received: %s\n", buf);
        exit(0);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    wait(NULL);
    wait(NULL);

    return 0;
}
