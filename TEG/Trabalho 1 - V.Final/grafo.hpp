#include <iostream>
#include <vector>
#include <stdio.h>      
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <math.h>
#include <list>
#include <stack>


using namespace std;

int calcularLog(int numVert); 
float distanciaPontos(float x, float y, float z, float w);
void gerarCoordenadasAleatorias(int numVertices, vector <pair <float, float>> &coordenadas);
bool verificarIndiceIgual(vector <pair <int, int>> indiceCoordenada, int first, int second);

class Grafo {
    int numVertices;
    vector <vector< pair<int, float>>> listaAdjacencia;   
public:
    Grafo (int numVertices);
    void ligarVizinhos(int numVer, vector<pair<float, float>> &coord);
    void descobrirVerticesProximos (vector <pair<float, float>> coordenada, int *vizinhosIndice, float *vizinhosCoordenadas, int vertice, int quantidadeVizinhos);
    void ordenarPesos (float *auxiliar_2);
    void adicionarArestas (vector <pair<float, float>> coordenada, vector <pair <int, int>> indiceCoordenada);
    void buscaemProfundidade();
};