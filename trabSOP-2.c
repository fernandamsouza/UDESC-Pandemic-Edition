#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h> 
#include <math.h>
#include <semaphore.h>
#include "lista.h"


typedef struct Matriz {
    int *linhaMatriz;
    int linha;
    int coluna;
    int id;
} Matriz;

Matriz argumentos[20];

//sem_t s1;

pthread_barrier_t barreira;

Lista *li;

void *impares (void *m) {
    printf ("a");
    pthread_barrier_wait(&barreira);
    Matriz *aux = m;
    int *linham = aux->linhaMatriz;
    int l = aux->linha;
    int coluna = aux->coluna;
    int id = aux->id;
    int i;
    long total = 0;
    for (i= 0; i < coluna; i++) {
        if (((int)linham[i] % 2) != 0) {
            printf ("%d\n", linham[i]);
            total++;
        }
    }
    insere_lista_final(li, total, id);
    pthread_exit(NULL);
}


int main(int argc, char * argv[]) {
    int num_threads = atoi(argv[1]), linhas = num_threads, colunas = atoi(argv[2]);
    int x, y, id;
    int **MATRIZ;

    pthread_t thread_id[num_threads];

    MATRIZ = (int ** ) malloc(sizeof(int * ) * (colunas * linhas));
    if (MATRIZ == NULL) {
        printf ("Falha na alocacao de memoria");
        exit(EXIT_FAILURE);
        return 2;
    }
    for (x = 0; x < linhas; x++) {
        MATRIZ[x] = (int *) malloc(colunas * sizeof(int));
        for (y = 0; y < colunas; y++) {
            MATRIZ[x][y] = rand()%100; // gera números entre 0 e 99
            printf ("%d ", MATRIZ[x][y]);
        }
        printf ("\n");
    }
    int cont =0;
    int as=0;

    li = cria_lista();
    pthread_barrier_init(&barreira, NULL, num_threads);
    for (id = 0; id<num_threads; id++) {
        printf ("id=%d\n", id);
        argumentos[id].linha = linhas;
        argumentos[id].coluna = colunas;
        argumentos[id].linhaMatriz = MATRIZ[as];
        argumentos[id].id = id;
        cont++;
        pthread_create(&thread_id[id], NULL, impares, (void *) &argumentos[id]);
        printf("cont=%d\n", cont);
        as++;
    }

    int total=0, totaltotal=0;

    for (id = 0; id < num_threads; id++) {
        pthread_join(thread_id[id], NULL);
        //printf ("thread %d =>    %d impares\n",id, total);
        totaltotal += li->infoss[id].impares;
    }
    mostrarTodos(li);
    printf ("---------------------------------\n");
    printf ("Total = %d primos\n", totaltotal);
    libera_lista(li);
}