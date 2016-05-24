#Makefile :: grafo

all: list.o graph.o main.o
	 gcc -o Graph list.o graph.o main.o -lm

list.o: list.c
	gcc -c list.c

graph.o: graph.c
	gcc -c graph.c

main.o: main.c
	gcc -c main.c

run:
	./Graph
