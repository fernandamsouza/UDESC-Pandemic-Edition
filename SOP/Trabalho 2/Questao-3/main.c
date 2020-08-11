// Fernanda Maria de Souza.
// Executar com:
// 1 - make
// ou 
// 2 - gcc main.c funcoes.c -o questao_3 funcoes.h && ./questao_3 3 
// Após, digitar os números de páginas.

#include "funcoes.h"

int main(int argc, char *argv[]) {
	int quantidade_paginas = 0; // Irá guardar a quantidade de páginas lidas.
	// R1 - O programa recebe o número de páginas físicas na memória(npf) com um parâmetro na linha de comando. Você pode assumir que um número de página cabe em um long.
	int npf = atoi(argv[1]);  // Número de páginas físicas.
	int *p_ref; // Ponteiro que irá guardar a referência as páginas.
	int *input;
	input = malloc(sizeof(int) * (10 * npf));
	p_ref = malloc(sizeof(int) * (10 * npf));
	// R2 - O programa deve ler da entrada padrão uma sequência de números de página, a qual é encerrada por -1.
	printf("Digite os números de página:\n"); 
	while(1) {
        scanf("%d", &input[quantidade_paginas]);
        if(input[quantidade_paginas] == -1)
            break;
		quantidade_paginas++;
    }
	printf("\nPáginas lidas: ");
	for (int t = 0; t < quantidade_paginas; t++) {
		*(p_ref+(t)) = input[t];
		printf("%d ", *(p_ref+t));
	}
	printf("\nTotal: %d\n", quantidade_paginas);
	// R7 - Ao final da execução, o programa deve imprimir o número de faltas de página para cada algoritmo.
	// Obs.: Fiquei em dúvida se era o Least ou o Most, então fiz os dois.
	printf("FIFO:		%d faltas de pagina.\n", fifo(npf, p_ref, quantidade_paginas));
	printf("LRU(Least):	%d faltas de pagina.\n", lru(npf, p_ref, quantidade_paginas));
    printf("MRU(Most):	%d faltas de pagina.\n", mru(npf, p_ref, quantidade_paginas));
}

