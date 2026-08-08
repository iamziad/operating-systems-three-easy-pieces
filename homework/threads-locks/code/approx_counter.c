#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THRDS 15
#define ITERATIONS 1000000
#define THRSHOLD 1000

// prevents false sharing
typedef struct {
    uint32_t value;
    uint8_t padding[60];
} PaddedInt;

typedef struct {
    PaddedInt lvalue[NUM_THRDS];
    int gvalue;
    pthread_mutex_t glock;
} Counter;

typedef struct {
    Counter *c;
    int thrd;
} UpdateArgs;

void counter_init(Counter *c)
{
    pthread_mutex_init(&c->glock, NULL);
    c->gvalue = 0;

    for (int i = 0; i < NUM_THRDS; i++) {
        c->lvalue[i].value = 0;
    }
}

void counter_destroy(Counter *c)
{
    pthread_mutex_destroy(&c->glock);
}

void *counter_update(void *args)
{
    UpdateArgs *ua = (UpdateArgs *)args;
    Counter *c = ua->c;
    int thrd_id = ua->thrd;

    for (int i = 0; i < ITERATIONS; i++) {
        c->lvalue[thrd_id].value++;

        if (c->lvalue[thrd_id].value >= THRSHOLD) {
            pthread_mutex_lock(&c->glock);
            c->gvalue += c->lvalue[thrd_id].value;
            pthread_mutex_unlock(&c->glock);
            c->lvalue[thrd_id].value = 0;
        }
    }

    free(ua);
    return NULL;
}

int main(int argc, char *argv[])
{
    size_t padding = sizeof(PaddedInt);

    if (padding == (size_t)64)
        printf("false sharing is prevented\n");
    else
        printf("padding is not correctly set, %zu\n", padding);

    pthread_t thrds[NUM_THRDS];
    Counter counter;

    counter_init(&counter);

    for (int i = 0; i < NUM_THRDS; i++) {
        UpdateArgs *args = malloc(sizeof(UpdateArgs));
        args->c = &counter;
        args->thrd = i;
        pthread_create(&thrds[i], NULL, counter_update, (void *)args);
    }

    for (int i = 0; i < NUM_THRDS; i++)
        pthread_join(thrds[i], NULL);

    counter_destroy(&counter);

    printf("total: %d\n", counter.gvalue);

    return 0;
}
