#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define MAX 5

int buffer[MAX];
int fill_ptr, empty_ptr;
sem_t empty, fill, mutex;

void *producer(void *arg)
{
    for (int i = 0; i < 10; i++) {
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[fill_ptr] = i;
        fill_ptr = (fill_ptr + 1) % MAX;
        sem_post(&mutex);
        sem_post(&fill);
    }
    return NULL;
}

void *consumer(void *arg)
{
    for (int i = 0; i < 10; i++) {
        sem_wait(&fill);
        sem_wait(&mutex);
        int tmp = buffer[empty_ptr];
        empty_ptr = (empty_ptr + 1) % MAX;
        printf("consumed: %d\n", tmp);
        sem_post(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    sem_init(&empty, 0, 5);
    sem_init(&fill, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_t t1, t2;
    pthread_create(&t1, NULL, producer, NULL);
    pthread_create(&t2, NULL, consumer, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
