#ifndef ARESTA_H
#define ARESTA_H

#include <iostream>
#include <vector>

#include "Vertice.hpp"

class Vertice;

class Aresta {
    friend class Vertice;

   public:
    Aresta(Vertice* v1, Vertice* v2);
    ~Aresta();

    const std::vector<Vertice*>& getVertices() const;

   private:
    std::vector<Vertice*> vertices;
};

#endif