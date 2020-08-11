all: questao_3

questao_3: main.o funcoes.o
	gcc main.o funcoes.o -o questao_3

main.o:
	gcc -c main.c

funcoes.o: funcoes.c funcoes.h
	gcc -c funcoes.c funcoes.h

t1:
	./questao_3 3

clean:
	rm questao_3 *.o
