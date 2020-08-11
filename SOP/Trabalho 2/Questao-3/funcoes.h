// Fernanda Maria de Souza.
// Executar com:
// 1 - make
// ou 
// 2 - gcc main.c funcoes.c -o questao_3 funcoes.h && ./questao_3 3 
// Após, digitar os números de páginas.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contemMemoriaFisica(int vetor_fisico[], int npf, int numeros_de_pagina);
int fifo(int npf, int p_ref[], int quantidade_paginas);
int lru(int npf, int p_ref[], int quantidade_paginas);
int mru(int npf, int p_ref[], int quantidade_paginas);
