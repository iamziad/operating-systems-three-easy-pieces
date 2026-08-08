#include <pthread.h>
#include <stdio.h>

volatile int counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *worker(void *args)
{
    pthread_mutex_lock(&lock);
    for (int i = 0; i < 1000000; i++)
        counter++;
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main()
{
    pthread_t thrds[15];

    for (int i = 0; i < 15; i++) {
        pthread_create(&thrds[i], NULL, worker, NULL);
    }

    for (int i = 0; i < 15; i++) {
        pthread_join(thrds[i], NULL);
    }

    printf("counter = %d\n", counter);

    return 0;
}
