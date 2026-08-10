#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define MAX 5

int buffer[MAX];
int fill_ptr, empty_ptr;
sem_t empty, fill;

void *producer(void *arg)
{
    for (int i = 0; i < 10; i++) {
        buffer[fill_ptr] = i;
        fill_ptr = (fill_ptr + 1) % MAX;
        sem_wait(&empty);
    }
    return NULL;
}

void *consumer()
{
    for (int i = 0; i < 10; i++) {
        int tmp = buffer[empty_ptr];
        empty_ptr = (empty_ptr + 1) % MAX;
        printf("consumed: %d\n", tmp);
        sem_post(&empty);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    sem_init(&empty, 0, 5);
    sem_init(&fill, 0, 0);

    pthread_t t1, t2;
    pthread_create(&t1, NULL, producer, NULL);
    pthread_create(&t2, NULL, producer, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
