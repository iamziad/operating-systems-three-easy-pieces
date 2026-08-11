#include <pthread.h>
#include <stdio.h>

int shared_data = 10;
pthread_rwlock_t rw = PTHREAD_RWLOCK_INITIALIZER;

void *reader(void *arg)
{
    int id = *((int *)arg);

    pthread_rwlock_rdlock(&rw);

    printf("Reader<%d>: read shared_data = %d\n", id, shared_data);

    pthread_rwlock_unlock(&rw);

    return NULL;
}

void *writer(void *arg)
{
    int id = *((int *)arg);

    pthread_rwlock_wrlock(&rw);

    shared_data <<= 1;

    printf("Writer<%d>: UPDATED shared_data -> %d\n", id, shared_data);

    pthread_rwlock_unlock(&rw);

    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t readers[10];
    pthread_t writers[2];
    size_t readers_size = sizeof(readers) / sizeof(pthread_t);
    size_t writers_size = sizeof(writers) / sizeof(pthread_t);

    for (size_t i = 0; i < readers_size; i++) {
        pthread_create(&readers[i], NULL, reader, (void *)&i);
    }

    for (size_t i = 0; i < readers_size; i++) {
        pthread_join(readers[i], NULL);
    }

    for (size_t i = 0; i < writers_size; i++) {
        pthread_create(&writers[i], NULL, writer, (void *)&i);
    }

    for (size_t i = 0; i < writers_size; i++) {
        pthread_join(writers[i], NULL);
    }

    return 0;
}
