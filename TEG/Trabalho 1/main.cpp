#include <iostream>
#include <vector>
#include <stdio.h>      
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <math.h>

using namespace std;

class Grafo {
    int numVertices;
public:
    Grafo (int numVertices); // construtor
};


// Função para gerar números aleatórios entre 0 e 1
void gerarCoordenadasAleatorias(int numVertices, vector <pair <float, float>> &coordenadas) {
    float x, y;
    for (int i = 0; i < numVertices; i++) {
        x = 0 + 1.0*((float)(rand())/RAND_MAX);
        y = 0 + 1.0*((float)(rand())/RAND_MAX);
        pair <float, float> coordaux (x,y);
        coordenadas.push_back(coordaux); // colocar as coordenadas no fim do vetor
        printf("[%d]\n x: %.5f  y: %.5f\n", i, coordaux.first, coordaux.second);
    }    
}

int main() {
    int numVertices = 50;
    //Grafo grafo(numVertices);
    vector <pair <float, float>> coordenadas;
    gerarCoordenadasAleatorias(numVertices, coordenadas);
    return 0;
}