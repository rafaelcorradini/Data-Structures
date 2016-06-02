#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"abb.h"

abb *defineABB() {
	abb *T;
	T = malloc(sizeof(abb));
	if(T == NULL) {
		printf("Memória insuficiente");
		return NULL;
	} 
	T->nelem = 0;
	return T;
}

boolean isEmpty(abb *T) {
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

map_node *searchElem(abb *T, int id, map_node *n) {
	if (isEmpty(T)) return NULL;
	if (isExternal(n)) {
		return n;
	} else {
		if (strcmp(k, n->elem.chave) > 0) { 
			return searchElem(T, k, n->rightChild);
		} else if (strcmp(k, n->elem.chave) < 0) {
			return searchElem(T, k, n->leftChild);
		} else {
			return n;
		}
	}
}

map_node *sibling(map_node *n) {
	if (n->parent->rightChild == n) {
		return n->parent->leftChild;
	} else {
		return n->parent->rightChild;
	}
}

boolean expandExternal(abb *T, map_node *n) {
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

tipo_elem removeAboveExternal(abb *T, map_node *n) {
	map_node *v;
	tipo_elem el = n->elem;
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
		if (strcmp(n->elem.chave, n->parent->elem.chave) < 0) {
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

map_node *replaceElem(tipo_elem el, map_node *n) {
	if (isExternal(n) || n == NULL) return NULL;
	n->elem = el;
	return n;
}

tipo_elem removeElem(abb *T, int id) {
	map_node *s, *n;
	tipo_elem el = {"",""}, els;
	n = searchElem(T, k, T->root);
	if (isExternal(n) || n == NULL) return el;
	el = n->elem;

	if (isExternal(n->leftChild) || isExternal(n->rightChild)) {
		removeAboveExternal(T, n);
	} else {
		s = substitute(T, n->leftChild);
		els = s->elem;
		removeAboveExternal(T, s);
		replaceElem(els, n);
	}
	return el;
}

map_node *substitute(abb *T, map_node *n) {
	if(n->rightChild != NULL) {
		return substitute(T, n->rightChild);
	} else {
		return n->parent;
	}
}

map_node *insertElem(abb *T, tipo_elem el) {
	map_node *n;
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
		n = searchElem(T, el.chave, T->root);
		n->elem = el;
		T->nelem++;
		expandExternal(T,n);
		return n;
	}
}

void freeNodes(abb *T, map_node *n) {
	if (T->nelem == 0) exit(1);

	if (n->leftChild != NULL)
		freeNodes(T, n->leftChild);
	if (n->rightChild != NULL)
		freeNodes(T, n->rightChild);

	if (!isExternal(n))
		T->nelem--;
	free(n);
	
}

void printABB(abb *T, map_node *n) {
	if (isEmpty(T)) {
		printf("Arvore vazia");
	} else {
		if (!isExternal(n)) {
			printABB(T, n->leftChild);
			printf("%s\n", n->elem.chave);
			printABB(T, n->rightChild);
		}
	}
	
}