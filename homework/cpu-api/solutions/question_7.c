#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

/*
  here the child closed it's own copy of the stdout, but the parent still can
  print smth in the stdout, because the open file descriptor of the stdout in
  the kernel still didn't get deleted, because the parent still has a reference
  to it.
 */

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
        close(STDOUT_FILENO);
        if (printf("can i print something?") > 0) {
            exit(1);
        }
        exit(0);
    }
    default:
        char *msg = "parent: started\n";
        write(STDERR_FILENO, msg, strlen(msg));
        int status;
        waitpid(-1, &status, 0);
        if (WIFEXITED(status) != 0) {
            printf("parent: the child couldn't print smth\n");
            printf("exit status: %d\n", WEXITSTATUS(status));
        }
        break;
    }
    return 0;
}
