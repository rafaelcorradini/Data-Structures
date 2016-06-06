#include <stdio.h>
#include <stdlib.h>
#include "map.h"

Map *define() {
	return defineABB();
}

Map_elem searchMap(Map *M, int id) {
	Map_elem el = {0, NULL};
	if(isEmpty(M)) return el;
	if(searchElem(M, id, root(M)) == NULL || isExternal(searchElem(M, id, root(M)))) return el;
	return searchElem(M, id, root(M))->elem;
}

boolean insertMap(Map *M, Map_elem x) {
	if (!isEmpty(M)) {
		if (!isExternal(searchElem(M, x.id, root(M)))) return FALSE;
	}
	if (insertElem(M,x) != NULL) {
		return TRUE;
	} else {
		printf("Espaco insuficiente na memoria");
		return FALSE;
	}
}

boolean replaceMap(Map *M, Map_elem x) {
	if (isEmpty(M)) return FALSE;
	if (replaceElem(x, searchElem(M, x.id, root(M))) != NULL) return TRUE;
	else return FALSE;
}

Map_elem removeMap(Map *M, int id) {
	Map_elem el = {0, NULL};
	if (isEmpty(M)) return el;
	return removeElem(M, id);
}

int getLastMap(Map *M) {
	return getLastAbb(M);
}

void distVector(Map *M, double **D) {
	distVectorAux(M, D, root(M));
}

void printMap(Map *M, char op) {
	printABB(M, root(M), op);
}

void freeMap(Map *M, map_node *n) {
	freeNodes(M, root(M));
}