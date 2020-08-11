all: teg

teg: main.o grafo.o
	g++ main.o grafo.o -o teg 

main.o:
	g++ -c main.cpp

grafo.o: grafo.cpp grafo.hpp
	g++ -c grafo.cpp grafo.hpp

clean:
	rm teg *.o
