#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

Lista *cria_lista(void) {
	Lista *li;
	li = (Lista *)malloc(sizeof(Lista));
    li->infoss = (struct infos*)malloc(sizeof(struct infos));
	if(li != NULL){
		li->qtd = 0;
	}
	return li;
}

void libera_lista(Lista *li) {
	free(li);
}

int lista_vazia(Lista *li) {
	if(li == NULL){
		return -1;
	}else{
		return (li->qtd == 0);
	}
}

int insere_lista_final(Lista *li, int impares, int id) {
	if(li == NULL) {
		return 0;
	}
	li->infoss[li->qtd].thread_id = id;
	li->infoss[li->qtd].impares = impares;
	li->qtd++;
	return 1;
}

void mostrarTodos(Lista *li) {
	if(li->qtd == 0) {
		printf("Lista Vazia\n");
	} else{
		for (int i = 0; i < li->qtd; i++) {
			printf ("thread %d =>    %d impares\n", li->infoss[i].thread_id ,li->infoss[i].impares);
			printf("\n");
		}
    }
}