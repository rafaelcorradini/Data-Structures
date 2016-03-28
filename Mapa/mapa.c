#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"mapa.h"

abb *define() {
	return defineABB();
}

tipo_elem search(char k[30], abb *M) {
	tipo_elem el = {"",""};
	if(isEmpty(M)) return el;
	if(searchElem(M, k, M->root) == NULL || isExternal(searchElem(M, k, M->root))) return el;
	return searchElem(M, k, M->root)->elem;
}

boolean insert(tipo_elem x, abb *M) {
	if (!isEmpty(M)) {
		if (!isExternal(searchElem(M, x.chave, M->root))) return FALSE;
	}
	if (insertElem(M,x) != NULL) {
		return TRUE;
	} else {
		printf("Espaco insuficiente na memoria");
		return FALSE;
	}
}

boolean replace(tipo_elem x, abb *M) {
	if (isEmpty(M)) return FALSE;
	if (replaceElem(x, searchElem(M, x.chave, M->root)) != NULL) return TRUE;
	else return FALSE;
}

tipo_elem remover(char k[30], abb *M) {
	tipo_elem el = {"",""};
	if (isEmpty(M)) return el;
	return removeElem(M, k);
}

void print(abb *M) {
	printABB(M, M->root);
}

void freeNodesMap(abb *M, node *n) {
	freeNodes(M, n);
}