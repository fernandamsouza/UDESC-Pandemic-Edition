#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

#define MAX 2000

int x = 2;
int ok = 0;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void f1(void *argp)
{
    pthread_mutex_lock(&m);
    while (!ok)
    {
        pthread_cond_wait(&c, &m);
    }
    x = x * 3;
    pthread_mutex_unlock(&m);
}

void f2(void *argp)
{
    pthread_mutex_lock(&m);
    x = x + 15;
    ok = 1;
    pthread_cond_signal(&c);
    pthread_mutex_unlock(&m);
}

int main(void)
{
    pthread_t t1, t2;
    int rc;
    rc = pthread_create(&t1, NULL, (void *)f1, NULL);
    rc = pthread_create(&t2, NULL, (void *)f2, NULL);
    rc = pthread_join(t1, NULL);
    rc = pthread_join(t2, NULL);
    printf("x=%d\n", x);
    return 0;
}