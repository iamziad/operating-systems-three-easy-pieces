#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t s;
int counter;

void *count(void *arg)
{
    int local = 0;

    for (int i = 0; i < 1000000; i++) {
        local++;
    }

    sem_wait(&s);
    counter += local;
    sem_post(&s);

    return NULL;
}

int main(int argc, char *argv[])
{
    sem_init(&s, 0, 1);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, count, NULL);
    pthread_create(&t2, NULL, count, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("counter %d\n", counter);
    return 0;
}
