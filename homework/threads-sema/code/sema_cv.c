#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t s;

void *child(void *arg)
{
    printf("child\n");
    sem_post(&s);
    return NULL;
}

int main(int argc, char *argv[])
{
    sem_init(&s, 0, 0);
    pthread_t t;
    pthread_create(&t, NULL, child, NULL);
    sem_wait(&s);
    printf("parnet\n");
    return 0;
}
