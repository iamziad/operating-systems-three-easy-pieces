#include <pthread.h>
#include <stdio.h>

#define LOOPS 10
#define MAX 5

static int buffer[MAX];
static int fill_ptr;
static int empty_ptr;
static int count; // num of elements stored in buffer
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t fill = PTHREAD_COND_INITIALIZER;

void put(int val)
{
    buffer[fill_ptr] = val;
    fill_ptr = (fill_ptr + 1) % MAX;
    count++;
}

int get()
{
    int val = buffer[empty_ptr];
    empty_ptr = (empty_ptr + 1) % MAX;
    count--;
    return val;
}

void *producer(void *arg)
{
    for (size_t i = 0; i < LOOPS; i++) {
        pthread_mutex_lock(&m);
        while (count == MAX) {
            pthread_cond_wait(&empty, &m);
        }
        put(i);
        pthread_cond_signal(&fill);
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

void *consumer(void *arg)
{
    for (int i = 0; i < LOOPS; i++) {
        pthread_mutex_lock(&m);
        while (count == 0) {
            pthread_cond_wait(&fill, &m);
        }
        int tmp = get();
        printf("consumed %d\n", tmp);
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, producer, NULL);
    pthread_create(&t2, NULL, consumer, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
