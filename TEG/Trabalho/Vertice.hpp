#ifndef VERTICE_H
#define VERTICE_H

#include <list>
#include <vector>

#include "Aresta.hpp"

class Aresta;

class Vertice {
    friend class Aresta;

   public:
    static int id;

    Vertice(const float x, const float y);
    ~Vertice();

    float getX() const;

    float getY() const;

    int getId() const;

     std::list<Vertice*>& getVizinhos();

     void setVizinho(Vertice* v);

   private:
    

    float x,y;
    int idS;
    std::list<Vertice*> vizinhosId;
    std::list<Aresta*> arestas;
};

#endif