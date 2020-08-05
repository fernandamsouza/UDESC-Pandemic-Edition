#include "Aresta.hpp"

Aresta::Aresta(Vertice* v0, Vertice* v1) {
    unsigned short c = 0;
    if (v0 != nullptr && v1 != nullptr) {
        this->vertices.push_back(v0);
        this->vertices.push_back(v1);
        if (!v0->getVizinhos().empty()) {
            for (std::list<Vertice*>::iterator it = v0->getVizinhos().begin();it!= v0->getVizinhos().end();it++) {
                //std::cout << "Vizinho v0: " << v0->getVizinhos().at(i) << " comparado com: " << v1->getId() << std::endl;
                if ((*it) == v1) {
                    //std::cout<<"Quebrou"<<std::endl;
                    c = 1;
                    //std::cout<<c<<std::endl;
                    break;
                }
            }
            if (c != 1) {
                //std::cout<<"Adicionando vizinho v0"<<std::endl;
                v0->setVizinho(v1);
            }
        } else {
            //std::cout<<"Adicionando vizinho v0"<<std::endl;
            v0->setVizinho(v1);
        }
        c = 0;
        if (!v1->getVizinhos().empty()) {
            for (std::list<Vertice*>::iterator it = v1->getVizinhos().begin();it!= v1->getVizinhos().end();it++) {
                //std::cout << "Vizinho v1: " << v1->getVizinhos().at(i) << " comparado com: " << v0->getId() << std::endl;
                if ((*it) == v0) {
                    //std::cout<<"Quebrou"<<std::endl;
                    c = 1;
                    //std::cout<<c<<std::endl;
                    break;
                }
            }
            if(c != 1){
                //std::cout<<"Adicionando vizinho v1"<<std::endl;
                v1->setVizinho(v0);
            }
        } else {
            //std::cout<<"Adicionando vizinho v1"<<std::endl;
            v1->setVizinho(v0);
        }
    } else {
        std::cerr << "Erro ao inserir vertices" << std::endl;
    }
}

Aresta::~Aresta() {
    for (std::vector<Vertice*>::iterator it = this->vertices.begin(); it != this->vertices.end(); it++) {
        delete *it;
    }
    this->vertices.clear();
}

const std::vector<Vertice*>& Aresta::getVertices() const {
    if (!this->vertices.empty()) {
        return this->vertices;
    } else {
        std::cerr << "Nenhum vertice na aresta" << std::endl;
        return this->vertices;
    }
}
