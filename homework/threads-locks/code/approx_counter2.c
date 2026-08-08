#include <pthread.h>
#include <stdio.h>

int counter;
pthread_mutex_t glock = PTHREAD_MUTEX_INITIALIZER;

void *worker(void *args)
{
    int local = 0;

    for (int i = 0; i < 1000000; i++) {
        local++;

        if (local >= 1000) {
            pthread_mutex_lock(&glock);
            counter += local;
            pthread_mutex_unlock(&glock);
            local = 0;
        }
    }

    if (local >= 1000) {
        pthread_mutex_lock(&glock);
        counter += local;
        pthread_mutex_unlock(&glock);
        local = 0;
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t thrds[15];

    for (int i = 0; i < 15; i++) {
        pthread_create(&thrds[i], NULL, worker, NULL);
    }

    for (int i = 0; i < 15; i++) {
        pthread_join(thrds[i], NULL);
    }

    printf("counter: %d\n", counter);
    pthread_mutex_destroy(&glock);

    return 0;
}
