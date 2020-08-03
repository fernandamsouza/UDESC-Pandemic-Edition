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
    Grafo (int numVertices); // Construtor
    int calcularLog(int numVertices); 
    float distanciaPontos(float x, float y, float z, float w);
    void gerarCoordenadasAleatorias(int numVertices, vector <pair <float, float>> &coordenadas);
};


// Função para descobrir os vizinhos de cada vértice: K pontos mais próximos
int calcularLog(int numVertices) {
    int k;
    if (numVertices == 0) {
        return 1;
    }
    k = log2(numVertices);
    return k;
}

// Função para descobrir o peso de uma aresta entre dois pontos.
float distanciaPontos(float x, float y, float z, float w) {
    float p1 = x - z;
    float p2 = y - w;
    p1 = p1*p1;
    p2 = p2*p2;
    float s = p1 + p2;
    return sqrt(s);
}


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
    //float r = distanciaPontos(2.0,3.0,4.0,5.0); teste -> ok
    //int r2 = calcularLog (50); teste - > ok
    printf("%f, %d", r, r2);
    return 0;
}