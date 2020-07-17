#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS    5

void *PrintHello(void *arg) {
   long tid = (long)arg;
   printf("Alo da thread %ld\n",
          tid);
   pthread_exit((void *)tid);
}

int main (int argc, char *argv[]) {
   pthread_t threads[NUM_THREADS+3];
   int rc;
   long t, ret=0;
   void *status;
   for (t=0; t<NUM_THREADS+3; t++){
      printf("main: criando thread %ld\n", t);
      rc = pthread_create(&threads[t],
                          NULL,
                          PrintHello,
                          (void *)t);
                          pthread_join(threads[t], &status);
                          ret += (long) status;
      if (rc) {
         printf("ERRO - rc=%d\n", rc);
         exit(-1);
      }
   }
   for (t=0; t<NUM_THREADS; t++){
      printf("main: criando thread %ld\n", t);
      rc = pthread_create(&threads[t],
                          NULL,
                          PrintHello,
                          (void *)t);
      pthread_join(threads[t], &status);
      ret += (long) status;
      if (rc) {
         printf("ERRO - rc=%d\n", rc);
         exit(-1);
      }
   }
   printf ("\n%lu\n", ret);
   /* Ultima coisa que main() deve fazer */
   pthread_exit(NULL);
}
