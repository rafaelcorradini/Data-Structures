#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List *initList() {
	List *L;
	L = (List*) malloc(sizeof(List));
	L->head = NULL;
	L->tail = NULL;
	L->count = 0;
	return L;
}

void freeList(List *L, Node *n) {
	if(L->head == NULL) {
		free(L);
		return;
	}
	if(n->next != NULL)
		freeList(L, n->next);

	if(n->el != NULL)
		free(n->el);

	if(n == L->head) {
		free(n);
		free(L);
		return;
	} else {
		free(n);
	}
}

Node *insertList(List *L) {
	Node *p;
	p = (Node*) malloc(sizeof(Node));
	if(L->head == NULL) {
		p->prev = NULL;
		L->head = p;
		L->tail = p;
	} else {
		L->tail->next = p;
		p->prev = L->tail;
		L->tail = p;
	}
	p->next = NULL;
	p->el = NULL;
	L->count++;
	return p;
}

void *removeList(List *L, Node *n) {
	void *aux = NULL;

	if(n == NULL)
		return aux;
	aux = n->el;	
	if (L->tail == n && L->head == n) {
		L->head = NULL;
		L->tail = NULL;
	} else if (L->head == n) {
		L->head = n->next;
		L->head->prev = NULL;
	} else if (L->tail == n) {
		L->tail = n->prev;
		L->tail->next = NULL;
	} else {
		n->prev->next = n->next;
		n->next->prev = n->prev;
	}
	free(n);
	L->count--;
	return aux;
}