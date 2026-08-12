#include <bits/time.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>

double timenow()
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (t.tv_sec * 1000.0) + (t.tv_nsec / 1000000.0);
}

int counter;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *count(void *arg)
{
    int local = 0;

    for (int i = 0; i < 1000000; i++) {
        local++;

        while (local >= 1000) {
            pthread_mutex_lock(&m);
            counter += local;
            local = 0;
            pthread_mutex_unlock(&m);
        }
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t thrds[12];

    double start = timenow();

    for (int i = 0; i < 12; i++)
        pthread_create(&thrds[i], NULL, count, NULL);

    for (int i = 0; i < 12; i++)
        pthread_join(thrds[i], NULL);

    pthread_mutex_destroy(&m);

    double end = timenow();

    printf("counter: %d\n", counter);
    printf("exectued in: %.2lfms\n", end - start);

    return 0;
}
