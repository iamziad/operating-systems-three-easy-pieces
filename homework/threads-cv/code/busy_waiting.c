#include <pthread.h>
#include <stdio.h>

// Very bad performance, wasted CPU cycles and memory leakage.

volatile int done = 0;

void *child(void *arg)
{
    printf("child\n");
    done = 1;
    return NULL;
}

int main(int argc, char *argv[])
{
    printf("parent begin\n");

    pthread_t c;
    pthread_create(&c, NULL, child, NULL);

    while (done == 0)
        ;

    printf("parent end\n");

    return 0;
}
