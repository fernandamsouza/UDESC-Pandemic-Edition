#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <list>
#include <vector>

#include "Aresta.hpp"
#include "Vertice.hpp"

class Grafo {
   public:
    Grafo();
    ~Grafo();

    void setVertice(Vertice* v);

    const std::list<Vertice*> getVertices() const;
    const std::list<Aresta*> getArestas() const;

    void addAresta(Vertice* v0, Vertice* v1);
    void remAresta(Vertice* v0, Vertice* v1); //pode remover ligaçao entre vertices
    void remAresta(Aresta* ar);// remove a aresta

    void addVertice(Vertice* v);
    void remVertice(Vertice* v);

    void imprimeGrafo();

    void DFS();
   private:

    void procP(Vertice* v, std::vector<unsigned int> pe, std::vector<unsigned int> ps, std::vector<Vertice*> pai, std::vector<unsigned char> arestas, unsigned int *c);

    std::list<Vertice*> vertices;
    std::list<Aresta*> arestas;
};

#endif