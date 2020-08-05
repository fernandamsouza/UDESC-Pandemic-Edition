#include "Vertice.hpp"

int Vertice::id = 0;

Vertice::Vertice(const float x, const float y) : x(x), y(y), idS{id} {
    Vertice::id++;
}

Vertice::~Vertice() {}

float Vertice::getX() const { return this->x; }

float Vertice::getY() const { return this->y; }

int Vertice::getId() const { return this->idS; }

void Vertice::setVizinho(Vertice* v) {
    this->vizinhosId.push_back(v);
    Aresta* a{new Aresta{this,v}};
    this->arestas.push_back(a);
}

std::list<Vertice*>& Vertice::getVizinhos() {
    return this->vizinhosId;
}