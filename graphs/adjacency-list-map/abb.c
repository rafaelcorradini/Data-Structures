#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "abb.h"

typedef struct {
    int value;
    List *adjacency;
} Vertex;

typedef struct {
    double value;
    Node* v1;
    Node* v2;
    Node* adj_v1;
    Node* adj_v2;
} Edge;


Map *defineABB() {
	Map *T;
	T = malloc(sizeof(Map));
	if(T == NULL) {
		printf("Memória insuficiente");
		return NULL;
	} 
	T->nelem = 0;
	T->lastId = 0;
	return T;
}

map_node *root(Map *T) {
	return T->root;
}

boolean isEmpty(Map *T) {
	if (T->nelem > 0) {
		return FALSE;
	} else {
		return TRUE;
	}
}

boolean isExternal(map_node *n) {
	if (n->leftChild == NULL && n->rightChild == NULL) {
		return TRUE;
	} else {
		return FALSE;
	}
}

map_node *searchElem(Map *T, int id, map_node *n) {
	if (isEmpty(T)) return NULL;
	if (isExternal(n)) {
		return n;
	} else {
		if (id > n->elem.id) { 
			return searchElem(T, id, n->rightChild);
		} else if (id < n->elem.id) {
			return searchElem(T, id, n->leftChild);
		} else {
			return n;
		}
	}
}

void distVectorAux(Map *T, double **D, int **P, map_node *n) {
	if (T->nelem == 0) return;
	
	if (!isExternal(n->leftChild))
		distVectorAux(T, D, P, n->leftChild);
	if (!isExternal(n->rightChild))
		distVectorAux(T, D, P, n->rightChild);

	if (!isExternal(n)) {
		D[n->elem.v1][n->elem.v2] = ((Edge*)(n->elem.node->el))->value;
		D[n->elem.v2][n->elem.v1] = ((Edge*)(n->elem.node->el))->value;
		P[n->elem.v1][n->elem.v2] = n->elem.v2;
		P[n->elem.v2][n->elem.v1] = n->elem.v1;
	}	
}

map_node *sibling(map_node *n) {
	if (n->parent->rightChild == n) {
		return n->parent->leftChild;
	} else {
		return n->parent->rightChild;
	}
}

boolean expandExternal(Map *T, map_node *n) {
	n->leftChild = NULL;
	n->rightChild = NULL;
	if (isExternal(n)) {
		n->leftChild = malloc(sizeof(map_node));
		n->rightChild = malloc(sizeof(map_node));
		n->leftChild->leftChild = NULL;
		n->leftChild->rightChild = NULL;
		n->rightChild->leftChild = NULL;
		n->rightChild->rightChild = NULL;
		if(n->leftChild == NULL && n->rightChild == NULL) return FALSE;
		n->leftChild->parent = n;
		n->rightChild->parent = n;
		return TRUE;
	} else {
		return FALSE;
	}	
}

Map_elem removeAboveExternal(Map *T, map_node *n) {
	map_node *v;
	Map_elem el = n->elem;
	if (n == T->root) {
		if (isExternal(n->leftChild) && isExternal(n->rightChild)) {
			free(n->rightChild);
			free(n->leftChild);
			free(n);
			T->root = NULL;
			T->nelem--;
			return el;
		} else if (isExternal(n->leftChild)) {
			T->root = n->rightChild; 
		} else {
		 	T->root = n->leftChild; 
		}
	} else {
		if(isExternal(n->rightChild)) {
			v = n->rightChild;
		} else {
			v = n->leftChild;
		}
		if (n->elem.id < n->parent->elem.id) {
			n->parent->leftChild = sibling(v);
		} else {
			n->parent->rightChild = sibling(v);
		}
		sibling(v)->parent = n->parent;
		free(v);
	}

	free(n);
	T->nelem--;
	return el;
}

map_node *replaceElem(Map_elem el, map_node *n) {
	if (isExternal(n) || n == NULL) return NULL;
	n->elem = el;
	return n;
}

void removeEdges(Map *T, int id, map_node *n) {
	if (n->leftChild != NULL)
		removeEdges(T, id, n->leftChild);
	if (n->rightChild != NULL)
		removeEdges(T, id, n->rightChild);
	if (n->elem.v1 == id || n->elem.v2 == id)
		removeElem(T, n->elem.id);
}

Map_elem removeElem(Map *T, int id) {
	map_node *s, *n;
	Map_elem el = {-1, NULL, -1, -1}, els;
	n = searchElem(T, id, T->root);
	if (isExternal(n) || n == NULL) return el;
	el = n->elem;

	if ((isExternal(n->leftChild) || isExternal(n->rightChild)) && T->root != n) {
		removeAboveExternal(T, n);
	} else {
		if (isExternal(n->leftChild))
			s = substituteRight(T, n->rightChild);
		else
			s = substituteLeft(T, n->leftChild);
		els = s->elem;
		removeAboveExternal(T, s);
		replaceElem(els, n);
	}
	return el;
}

map_node *substituteLeft(Map *T, map_node *n) {
	if(n->rightChild != NULL) {
		return substituteLeft(T, n->rightChild);
	} else {
		return n->parent;
	}
}

map_node *substituteRight(Map *T, map_node *n) {
	if(n->leftChild != NULL) {
		return substituteRight(T, n->leftChild);
	} else {
		return n->parent;
	}
}

map_node *insertElem(Map *T, Map_elem el) {
	map_node *n;

	T->lastId = el.id;

	if (isEmpty(T)) {
		n = malloc(sizeof(map_node));
		if(n == NULL) {
			printf("Memória insuficiente");
			return NULL;
		}
		n->elem = el;
		n->parent = NULL;
		T->root = n;
		T->nelem++;
		expandExternal(T,n);
		return n;
	} else {
		n = searchElem(T, el.id, T->root);
		n->elem = el;
		T->nelem++;
		expandExternal(T,n);
		return n;
	}
}

void freeNodes(Map *T, map_node *n) {
	if (T->nelem == 0) return;

	if (n->leftChild != NULL)
		freeNodes(T, n->leftChild);
	if (n->rightChild != NULL)
		freeNodes(T, n->rightChild);

	if (!isExternal(n))
		T->nelem--;
	free(n);
	
}

void printABB(Map *T, map_node *n, char op) {
	if (isEmpty(T)) {
		return;
	} else {
		if (!isExternal(n)) {
			printABB(T, n->leftChild, op);
			if (op == 'v')
				printf("%d %d\n", n->elem.id, ((Vertex*) n->elem.node->el)->value);
			else 
				if (n->elem.v2 > n->elem.v1)
					printf("%d %d %d %.3lf\n", n->elem.id, n->elem.v1, n->elem.v2, ((Edge*) n->elem.node->el)->value);
				else
					printf("%d %d %d %.3lf\n", n->elem.id, n->elem.v2, n->elem.v1, ((Edge*) n->elem.node->el)->value);
			printABB(T, n->rightChild, op);
		}
	}
	
}

int getLastAbb(Map *T) {
	return T->lastId;
}