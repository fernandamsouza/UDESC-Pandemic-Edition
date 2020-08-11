#include "grafo.hpp"

int main() {
    int opcao;
    printf ("\n");
    printf ("------------------------------------------------------------\n");
    printf ("-------------- TRABALHO 1 DE TEORIA DOS GRAFOS -------------\n");
    printf ("----- Alunos: Fernanda Maria de Souza e Nikolas Jensen -----\n");
    printf ("---------- Algoritmo: DFS - Busca em Profundidade ----------\n");
    printf ("------------------ Professor: Omir Alves -------------------\n");
    printf ("------------------------------------------------------------\n");
    do {
        printf ("\nSelecione a quantidade de vertices do grafo (Ou digite 0 para sair):\n");
        scanf("%d", &opcao);
        switch (opcao) {
            case 50: {
                int numVertices = 50;
                Grafo grafo(numVertices);
                vector <pair <float, float>> coordenadas;
                gerarCoordenadasAleatorias(numVertices, coordenadas);
                grafo.ligarVizinhos(numVertices, coordenadas);
                grafo.buscaemProfundidade();
                break;
            }
            case 100: {
                int numVertices = 100;
                Grafo grafo(numVertices);
                vector <pair <float, float>> coordenadas;
                gerarCoordenadasAleatorias(numVertices, coordenadas);
                grafo.ligarVizinhos(numVertices, coordenadas);
                grafo.buscaemProfundidade();
                break;
            }
            case 200: {
                int numVertices = 200;
                Grafo grafo(numVertices);
                vector <pair <float, float>> coordenadas;
                gerarCoordenadasAleatorias(numVertices, coordenadas);
                grafo.ligarVizinhos(numVertices, coordenadas);
                grafo.buscaemProfundidade();
                break;
            }
            case 300: {
                int numVertices = 300;
                Grafo grafo(numVertices);
                vector <pair <float, float>> coordenadas;
                gerarCoordenadasAleatorias(numVertices, coordenadas);
                grafo.ligarVizinhos(numVertices, coordenadas);
                grafo.buscaemProfundidade();
                break;
            }
            default: {
                printf ("\nEscolha uma opção válida da proxima vez :)\n");
                printf ("\n     Opções: 50, 100, 200 ou 300\n");
            }
        }
    } while (opcao!=0);
    return 0;
}