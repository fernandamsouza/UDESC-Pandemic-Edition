#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#define T_PAR 1
#define T_IMPAR 2

#define NELEM 2000000

int v[NELEM];

void *conta(void *tipo1)
{
     int i;
     long  total = 0;
     char tipo = (char)tipo1;

     for (i = 0; i < NELEM; i++) {
	  if ((tipo == T_PAR) && ((v[i] % 2) == 0))
	      total++;
	  else if ((tipo == T_IMPAR) && ((v[i] % 2) != 0))
	       total++;
     }
     pthread_exit((void *)total);
}

int main(int argc, char *argv[])
{
     int  i, rc;
     struct timeval tv_ini, tv_fim;
     void *status0, *status1;
     unsigned long time_diff, sec_diff, usec_diff, msec_diff;
     pthread_t threads[2];
     srandom(time(NULL));
     for (i = 0; i < NELEM; i++) {
	  v[i] = (int)random();
/*	  vetor[i] = i*2;*/
     }

     /* marca o tempo de inicio */
     rc = gettimeofday(&tv_ini, NULL);
     if (rc != 0) {
	  perror("erro em gettimeofday()");
	  exit(1);
     }
         rc = pthread_create(&threads[0],
                             NULL,
                             conta,
                             (void *)T_PAR);
                             pthread_join(threads[0], &status0);
                             long ret0 = (long) status0;
        rc = pthread_create(&threads[1],
                            NULL,
                         conta,
                         (void *)T_IMPAR);
                         pthread_join(threads[1], &status1);
                         long ret1 = (long) status1;
/*
     pares = conta(vetor, T_PAR);
     impares = conta(vetor, T_IMPAR)
*/
     /* marca o tempo de final */
     rc = gettimeofday(&tv_fim, NULL);
     if (rc != 0) {
	  perror("erro em gettimeofday()");
	  exit(1);
     }
     /* calcula a diferenca entre os tempos, em usec */
     time_diff = (1000000L*tv_fim.tv_sec + tv_fim.tv_usec) -
  	         (1000000L*tv_ini.tv_sec + tv_ini.tv_usec);
     /* converte para segundos + microsegundos (parte fracionária) */
     sec_diff = time_diff / 1000000L;
     usec_diff = time_diff % 1000000L;

     /* converte para msec */
     msec_diff = time_diff / 1000;

     printf("O vetor tem %lu numeros pares e %lu numeros impares.\n", ret0,
	    ret1);
/*     printf("Tempo de execucao: %lu.%06lu seg\n", sec_diff, usec_diff);*/
     printf("Tempo de execucao: %lu.%03lu mseg\n", msec_diff, usec_diff%1000);
     return 0;
}
