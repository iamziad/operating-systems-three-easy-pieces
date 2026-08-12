#include <bits/time.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>

double timenow()
{
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    return (time.tv_sec * 1000.0) + (time.tv_nsec / 1000000.0);
}

int counter;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *count(void *arg)
{
    int local = 0;

    for (int i = 0; i < 1000000; i++)
        local++;

    pthread_mutex_lock(&m);
    counter += local;
    pthread_mutex_unlock(&m);

    return NULL;
}

int main(int argc, char *argv[])
{
    double start = timenow();

    pthread_t thrds[15];

    for (int i = 0; i < 15; i++)
        pthread_create(&thrds[i], NULL, count, NULL);

    for (int i = 0; i < 15; i++)
        pthread_join(thrds[i], NULL);

    pthread_mutex_destroy(&m);

    double end = timenow();

    printf("counter %d\n", counter);
    printf("executed in %.2fms\n", end - start);

    return 0;
}
