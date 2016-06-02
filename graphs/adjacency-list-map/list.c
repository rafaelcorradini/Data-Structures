#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct {
	int count;
	Node *head, *tail;
} list;

list *initList() {
	list *l;
	l = (list*) malloc(sizeof(list));
	l->head = NULL;
	l->tail = NULL;
	l->count = 0;
	return l;
}

void eraseList(list *l, Node *n) {
	if(l->head == NULL) {
		free(l);
		return;
	}
	if(n->next != NULL)
		eraseList(l, n->next);

	free(n->next);
	free(n->next->el);

	if(n == l->head) {
		free(n->el);
		free(n);
		free(l);
	}	
}

Node *insert(list *l) {
	Node *p;
	p = (Node*) malloc(sizeof(Node));
	if(l->head == NULL) {
		p->next = NULL;
		p->prev = NULL;
		l->head = p;
		l->tail = p;
	} else {
		l->tail->next = p;
		p->prev = l->tail;
		p->next = NULL;
		l->tail = p;
	}
	l->count++;
	return p;
}

double remove(list *l, Node *n) {
	double aux = -1;

	if(n == NULL)
		return aux;
	aux = n->value;	
	if (l->tail == n && l->head == n) {
		l->head = NULL;
		l->tail = NULL;
	} else if (l->head == n) {
		l->head = n->next;
		l->head->prev = NULL;
	} else if (l->tail == n) {
		l->tail = n->prev;
		l->tail->next = NULL;
	} else {
		n->prev->next = n->next;
		n->next->prev = n->prev;
	}
	free(n->el);
	free(n);
	l->count--;
	return aux;
}

Node* find(list *l, int x) {
	Node *n;
	int i = 0;

	for (n = l->head; n != NULL; n != NULL? n = n->next) {
		i++;
		if (i == x)
			break;
	}

	return n;
}