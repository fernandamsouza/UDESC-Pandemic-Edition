// Fernanda Maria de Souza.
// Executar com:
// 1 - make
// ou 
// 2 - gcc main.c funcoes.c -o questao_3 funcoes.h && ./questao_3 3 
// Após, digitar os números de páginas.

#include "funcoes.h"

// Função auxiliar para retornar a posição da primeira instância de determinado número de página. Se dentro do vetor não conter o valor da página, retorna -1.
int contemMemoriaFisica(int vetor_fisico[], int npf, int numeros_de_pagina) {
	for (int i = 0; i < npf; i++)
		if (vetor_fisico[i] == numeros_de_pagina) {
			return i;
		}
	return -1;
}

// R6 - O Programa deve implementar os algoritmos de substituição de páginas FIFO e MRU.
int fifo(int npf, int p_ref[], int quantidade_paginas) {
	int fila[npf], faltas_de_pagina = 0;
	// R3 - O programa deve manter um controle de quais páginas lógicas estão alocadas na memória física.
	memset(fila, -1, sizeof(int) * npf);
	for (int i = 0; i < quantidade_paginas; i++) {	
	// R4 - O Programa deve verificar se a página lida está presente na memória física, se não estiver, ocorre uma falta de página.
		if(contemMemoriaFisica(fila, npf, p_ref[i]) == -1) {
			// R5 - Caso a memória física esteja ocupada, deve ser escolhida uma página vítima pelo FIFO, e a página correspondente é alocada para a página livre.
			// Continuação R3  - As páginas físicas são numeradas de 0 a npf − 1, e inicialmente estão todas vazias.
			// Shift 1 para esquerda -> páginas físicas de 0 a npf - 1.
			for (int j = 1; j < npf; j++) {
				fila[j - 1] = fila[j];
			}
			// A última posição do vetor fila recebe o valor do número de página analisado.
			fila[npf - 1] = p_ref[i];
			// Contador de faltas de página.
			faltas_de_pagina++;
		}
	}
	return faltas_de_pagina;
}

// R6 - O Programa deve implementar os algoritmos de substituição de páginas FIFO e MRU.
int lru(int npf, int p_ref[], int quantidade_paginas) {
	// indiceMemoriaFisica controla a última vez que uma página lógica foi alocada na memória física para selecionar a menos usada recentemente. É o vetor de posições do p_ref.
	int faltas_de_pagina = 0, memoriaFisica[npf], indiceMemoriaFisica[npf];
	// R3 - O programa deve manter um controle de quais páginas lógicas estão alocadas na memória física.
	memset(memoriaFisica, -1, sizeof(int) * npf);
	memset(indiceMemoriaFisica, -1, sizeof(int) * npf);

	for (int i = 0; i < quantidade_paginas; i++) {
		// R4 - O Programa deve verificar se a página lida está presente na memória física, se não estiver, ocorre uma falta de página.
		int resultado = contemMemoriaFisica(memoriaFisica, npf, p_ref[i]); 
		// resultado == -1 -> não contém na memória física.
		if (resultado == -1) {
			// R5 - Caso a memória física esteja ocupada, deve ser escolhida uma página vítima pelo FIFO, e a página correspondente é alocada para a página livre.
			int menorIndice = 0;
			// Se ocorrer uma falta de página, pega o MENOS usado recentemente e carrega a página para a página física correspondente. Assim, páginas antigas e menos usadas são as escolhas preferenciais.
			for (int j = 1; j < npf; j++) {
				// Acha o menor índice
				if (indiceMemoriaFisica[j] < indiceMemoriaFisica[menorIndice]) {
					menorIndice = j;
				}
			}
			memoriaFisica[menorIndice] = p_ref[i];
			indiceMemoriaFisica[menorIndice] = i;
			// Contador de faltas de página.
			faltas_de_pagina++;
		}
		else {
			indiceMemoriaFisica[resultado] = i; // Atualizar o contador dessa página para indicar que ela foi usada novamente.
		}
	}
	return faltas_de_pagina;
}

// R6 - O Programa deve implementar os algoritmos de substituição de páginas FIFO e MRU.
int mru(int npf, int p_ref[], int quantidade_paginas) {
	// indiceMemoriaFisica controla a última vez que uma página lógica foi alocada na memória física para selecionar a menos usada recentemente. É o vetor de posições do p_ref.
	int faltas_de_pagina = 0, memoriaFisica[npf], indiceMemoriaFisica[npf];
	// R3 - O programa deve manter um controle de quais páginas lógicas estão alocadas na memória física.
	memset(memoriaFisica, -1, sizeof(int) * npf);
	memset(indiceMemoriaFisica, -1, sizeof(int) * npf);

	for (int i = 0; i < quantidade_paginas; i++) {
		// R4 - O Programa deve verificar se a página lida está presente na memória física, se não estiver, ocorre uma falta de página.
		int resultado = contemMemoriaFisica(memoriaFisica, npf, p_ref[i]); 
		// resultado == -1 -> não contém na memória física.
		if (resultado == -1) {
			// R5 - Caso a memória física esteja ocupada, deve ser escolhida uma página vítima pelo FIFO, e a página correspondente é alocada para a página livre.
			int maiorIndice = 0;
			// Se ocorrer uma falta de página, pega o MAIS usado recentemente e carrega a página para a página física correspondente. Assim, páginas recentes e mais usadas são as escolhas preferenciais.
			for (int j = 1; j < npf; j++) {
				// Acha o maior índice
				if (indiceMemoriaFisica[j] > indiceMemoriaFisica[maiorIndice]) {
					maiorIndice = j;
				}
			}
			memoriaFisica[maiorIndice] = p_ref[i];
			indiceMemoriaFisica[maiorIndice] = i;
			// Contador de faltas de página.
			faltas_de_pagina++;
		}
		else {
			indiceMemoriaFisica[resultado] = i; // Atualizar o contador dessa página para indicar que ela foi usada novamente.
		}
	}
	return faltas_de_pagina;
}