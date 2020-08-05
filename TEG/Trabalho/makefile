parametrosCompilacao=-Wall #-Wshadow
projeto=grafo

all: $(projeto)

$(projeto): main.o Vertice.o Aresta.o Grafo.o
	g++ -o $(projeto) main.o Vertice.o Aresta.o Grafo.o $(parametrosCompilacao)

main.o: main.cpp
	g++ -c main.cpp $(parametrosCompilacao)

Vertice.o: Vertice.hpp Vertice.cpp
	g++ -c Vertice.cpp $(parametrosCompilacao)

Aresta.o: Aresta.hpp Aresta.cpp
	g++ -c Aresta.cpp $(parametrosCompilacao)

Grafo.o: Grafo.hpp Grafo.cpp
	g++ -c Grafo.cpp $(paramestrosCompilacao)

clean:
	rm -f *.o *.gch $(projeto)
