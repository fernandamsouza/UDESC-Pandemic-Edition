#include <stdio.h>
#include <stdlib.h>

struct infos {
    int impares;
    int linhas;
    int thread_id;
} Infos;

typedef struct lista {
	int qtd;
	struct infos *infoss;
} Lista;

Lista *cria_lista();

void libera_lista(Lista *li);
int lista_vazia(Lista *li);
int insere_lista_final(Lista *li, int impares, int id);
void mostrarTodos(Lista *li);