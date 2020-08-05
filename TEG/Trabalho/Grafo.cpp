#include "Grafo.hpp"

Grafo::Grafo() {
    /*std::cout<<this->arestas.()<<std::endl;
    std::list<Vertice*> l;
    this->vertices = l;

    std::list<Aresta*> a;
    this->arestas = a;*/
    std::cout << "Grafo criado" << std::endl;
}

Grafo::~Grafo() {
    std::cout << "Destruindo grafo" << std::endl;
    for (std::list<Vertice*>::iterator it = this->vertices.begin(); it != this->vertices.end(); it++) {
        delete *it;
    }
    for (std::list<Aresta*>::iterator it = this->arestas.begin(); it != this->arestas.end(); it++) {
        delete *it;
    }
}

void Grafo::setVertice(Vertice* v) {
    if (v != nullptr) this->vertices.push_back(v);
}

const std::list<Vertice*> Grafo::getVertices() const {
    if (!this->vertices.empty())
        return this->vertices;
    else {
        std::cerr << "Lista de vertices vazia" << std::endl;
        return this->vertices;
    }
}
const std::list<Aresta*> Grafo::getArestas() const {
    if (!this->arestas.empty())
        return this->arestas;
    else {
        throw std::out_of_range("Lista de arestas vazia");
        return this->arestas;
    }
}

void Grafo::addAresta(Vertice* v0, Vertice* v1) {
    std::list<Vertice*>::iterator it;
    unsigned char c = 0;
    if (v0 != v1) {
        for (it = this->vertices.begin(); it != this->vertices.end(); it++) {
            if (*it == v0) {
                (*(it))->setVizinho(v1);
                c++;
                if (c == 2) break;
            }else if(*it == v1){
                (*(it))->setVizinho(v0);
                c++;
                if (c == 2) break;
            }
        }
        if (it == this->vertices.end()) {
            std::cerr << "Vertices nao inclusos no grafo" << std::endl;
            return;
        }
    }
    //std::cout << "Adicionando aresta que liga " << v0->getId() << " e " << v1->getId() << std::endl;
    Aresta* a{new Aresta{v0, v1}};
    this->arestas.push_back(a);
}

void Grafo::remAresta(Vertice* v0, Vertice* v1) {
    unsigned short c = 0;
    if (v0 != nullptr && v1 != nullptr) {
        std::list<Aresta*>::iterator it;
        //std::cout<<"passou if"<<std::endl;
        for (it = this->arestas.begin(); it != this->arestas.end(); it++) {
            //std::cout<<"passou for1"<<std::endl;
            Vertice* aux0 = (*it)->getVertices().at(0);
            Vertice* aux1 = (*it)->getVertices().at(1);
            if ((aux0 == v0 && aux1 == v1) || (aux0 == v1 && aux1 == v0)) {
                //std::cout << "passou if2" << std::endl;
                //std::cout << "Aresta que liga: " << v0->getId() << " e " << v1->getId() << std::endl;
                for (std::list<Vertice*>::iterator itaux = v0->getVizinhos().begin(); itaux != v0->getVizinhos().end(); itaux++) {
                    if ((*itaux) == v1) {
                        //std::cout<<"passou if for"<<std::endl;
                        itaux = v0->getVizinhos().erase(itaux);
                    }
                }
                for (std::list<Vertice*>::iterator itaux = v1->getVizinhos().begin(); itaux != v1->getVizinhos().end(); itaux++) {
                    if ((*itaux) == v0) {
                        //std::cout<<"passou if for2"<<std::endl;
                        itaux = v1->getVizinhos().erase(itaux);
                    }
                }

                //delete *it;
                //std::cout<<"passou delete"<<std::endl;
                it = this->arestas.erase(it);
                //std::cout<<"passou erase"<<std::endl;
                c = 1;
            }

            //delete aux0;

            //delete aux1;
        }

        if (c == 0) {
            std::cerr << "Aresta nao encontrada" << std::endl;
        }
    } else {
        std::cerr << "Vertices nulos" << std::endl;
        return;
    }
}

void Grafo::remAresta(Aresta* ar) {
    if (ar != nullptr) {
        std::list<Aresta*>::iterator it;
        for (it = this->arestas.begin(); it != this->arestas.end(); it++) {
            if (*it == ar) {
                delete *it;
                it = this->arestas.erase(it);
            }
        }
        if (it == this->arestas.end()) {
            std::cerr << "Aresta nao encontrada" << std::endl;
            return;
        }
    } else {
        std::cerr << "Ponteiro nulo" << std::endl;
        return;
    }
}

void Grafo::addVertice(Vertice* v) {
    if (v != nullptr) {
        std::list<Vertice*>::iterator it;
        for (it = this->vertices.begin(); it != this->vertices.end(); it++) {
            if (v == *it) {
                std::cout << "Vertice ja inserido" << std::endl;
                return;
            }
        }
        if (it == this->vertices.end()) {
            this->vertices.push_back(v);
            //std::cout << "Adicionando vertice " << v->getId() << std::endl;
        }
    } else {
        std::cerr << "Vertice nulo" << std::endl;
        return;
    }
}

void Grafo::remVertice(Vertice* v) {
    if (v != nullptr) {
        std::list<Vertice*>::iterator it;
        std::list<Vertice*>::iterator it2;
        for (it = this->vertices.begin(); it != this->vertices.end(); it++) {
            if (v == *it) {
                std::cout << "Removendo vertice " << v->getId() << std::endl;
                /*for(it2 = v->getVizinhos().begin();it2!=v->getVizinhos().end();it2++){
                    std::cout<<(*it2)->getId()<<std::endl;
                    it2 = (*it2)->getVizinhos().erase(it);
                }*/
                

                it = this->vertices.erase(it);
                delete *it;
                break;
            }
        }
    } else {
        std::cerr << "Vertice nulo" << std::endl;
        return;
    }
}

void Grafo::imprimeGrafo() {
    std::cout << std::endl;
    for (std::list<Vertice*>::iterator it = this->vertices.begin(); it != this->vertices.end(); it++) {
        std::cout << "Vizinhos do vertice: " << (*it)->getId() << " -> ";
        for (std::list<Vertice*>::iterator itaux = (*it)->getVizinhos().begin(); itaux != (*it)->getVizinhos().end(); itaux++) {
            std::cout << (*itaux)->getId() << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Grafo::DFS() {
    int tam = this->vertices.size();
    std::vector<unsigned int> pe(tam);
    //pe.reserve(tam);
    std::vector<unsigned int> ps(tam);
    //ps.reserve(tam);
    std::vector<Vertice*> pai(tam);
    //pai.reserve(tam);
    std::vector<unsigned char> arestas;
    arestas.reserve(this->arestas.size());
    unsigned int *c, i = 0;
    *c = 0;
    for (std::list<Vertice*>::iterator it = this->vertices.begin(); it != this->vertices.end(); it++) {
        
        (*c)++;
        
        pe.at((*(it))->getId()) = *c;
        this->procP(*(it), pe, ps, pai, arestas, c);
    }
}

void Grafo::procP(Vertice* v, std::vector<unsigned int> pe, std::vector<unsigned int> ps, std::vector<Vertice*> pai, std::vector<unsigned char> arestas, unsigned int *c) {
    
    if (v->getVizinhos().size()>0) {
        
        for (std::list<Vertice*>::iterator it = v->getVizinhos().begin(); it != v->getVizinhos().end(); it++) {
            std::cout <<(*(it))->getId()<< std::endl;
            if (pe.at((*(it))->getId()) == 0) {
                arestas.at((v->getId())+(*(it))->getId()) = 0;
                std::cout <<"chegou"<< std::endl;
                pai.at((*(it))->getId()) = (*(it));
                
                this->procP((*(it)), pe, ps, pai, arestas, c);
            } else if (ps.at((*(it))->getId()) && (*(it)) != pai.at(v->getId()))
            {
                arestas.at((v->getId())+(*(it))->getId()) = 1;
            }
        }
        *c++;
        ps.at(v->getId()) = *c;
    }
    
}