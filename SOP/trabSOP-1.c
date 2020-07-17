#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s1;
sem_t s2;
sem_t s3;

#define MAX 2000

void *A(void *argp) {
    while(1) {
        sem_wait(&s1);
        printf("i");
        sem_post(&s2);
        sem_wait(&s1);
        printf("a");
        sem_post(&s2);
    }
}

void *B(void *argp) {
    int i;
    while (1) {
        for(i=0; i<2; i++) {
            sem_wait(&s2);
            printf("t");
            if (i==0) {
                printf(" ");
            }
            sem_post(&s3);
        }
    }
}

void *C(void *argp) {
    int j;
    while (1) {
        for (j=0; j<2; j++) {
            printf ("K");
            sem_post(&s1);
            sem_wait(&s3);
        }
        printf ("\n");
    }
}


int main(void)
{
    pthread_t t1, t2, t3;
    int rc;
    sem_init(&s1, 0, 0); /* mutex = 1 */
    sem_init(&s2, 0, 0); /* mutex = 1 */
    sem_init(&s3, 0, 0); /* mutex = 1 */
    rc = pthread_create(&t1, NULL, A, NULL);
    assert(rc == 0);
    rc = pthread_create(&t2, NULL, B, NULL);
    assert(rc == 0);
    rc = pthread_create(&t1, NULL, C, NULL);
    assert(rc == 0);
    rc = pthread_join(t1, NULL);
    assert(rc == 0);
    rc = pthread_join(t2, NULL);
    assert(rc == 0);
    rc = pthread_join(t3, NULL);
    assert(rc == 0);
    sem_destroy(&s1);
    sem_destroy(&s2);
    sem_destroy(&s3);
    printf("\n");
    return 0;
}