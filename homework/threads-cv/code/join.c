#include <pthread.h>
#include <stdio.h>

void *child(void *arg)
{
    printf("child\n");
    return NULL;
}

int main(int argc, char *argv[])
{
    printf("parent begin\n");

    pthread_t c;
    pthread_create(&c, NULL, child, NULL);
    pthread_join(c, NULL);

    printf("parent end\n");

    return 0;
}
