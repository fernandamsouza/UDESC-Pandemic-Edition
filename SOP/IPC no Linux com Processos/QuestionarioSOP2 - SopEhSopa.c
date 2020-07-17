#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s1;
sem_t s2;

#define MAX 2000

void *f1(void *argp)
{
    int i = 0;
    while (i < 2)
    {
        printf("SOP");
        sem_post(&s1);
        i++;
        sem_wait(&s2);
    }
    pthread_exit(NULL);
}

void *f2(void *argp)
{
    sem_wait(&s1);
    printf(" E");
    printf("H ");
    sem_post(&s2);
    sem_wait(&s1);
    printf("A!");
    sem_post(&s2);
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t t1, t2;
    int rc;

    sem_init(&s1, 0, 0); /* mutex = 1 */
    sem_init(&s2, 0, 0); /* mutex = 1 */
    rc = pthread_create(&t1, NULL, f1, NULL);
    assert(rc == 0);
    rc = pthread_create(&t2, NULL, f2, NULL);
    assert(rc == 0);
    rc = pthread_join(t1, NULL);
    assert(rc == 0);
    rc = pthread_join(t2, NULL);
    assert(rc == 0);
    sem_destroy(&s1);
    sem_destroy(&s2);
    printf("\n");
    return 0;
}