#include <iostream>

#include "Grafo.hpp"
#include "Aresta.hpp"
#include "Vertice.hpp"

int main(){
    Grafo *g{new Grafo{}};

    Vertice* v0{new Vertice{1.0,1.0}};
    Vertice* v1{new Vertice{2.0,2.0}};
    Vertice* v2{new Vertice{3.0,3.0}};
    Vertice* v3{new Vertice{4.0,4.0}};
    Vertice* v4{new Vertice{5.0,5.0}};
    Vertice* v5{new Vertice{6.0,6.0}};

    g->addVertice(v0); 
    
    g->addVertice(v1);
    g->addVertice(v2);
    g->addVertice(v3);
    g->addVertice(v4);
    g->addVertice(v5);
    g->addAresta(v0,v5);   
    g->addAresta(v0,v1);
    g->addAresta(v2,v2);
    g->addAresta(v5,v1);
    g->addAresta(v3,v3);
    g->addAresta(v5,v1);
    g->addAresta(v1,v4);

    g->remAresta(v0,v5);
    g->remAresta(v1,v0);

    g->remVertice(v1);
    
    g->DFS();

    g->imprimeGrafo();
    g->~Grafo();
}