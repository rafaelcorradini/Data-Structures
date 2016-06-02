#include <stdio.h>
#include <stdlib.h>
#include "list.h"

list *initList() {
	list *l;
	l = (list*) malloc(sizeof(list));
	l->head = NULL;
	l->tail = NULL;
	l->count = 0;
	return l;
}

void eraseList(list *l, node *n) {
	if(l->head == NULL) {
		free(l);
		return;
	}
	if(n->next != NULL)
		eraseList(l, n->next);

	free(n->next);

	if(n == l->head) {
		free(n);
		free(l);
	}	
}

node *insert(list *l, type_elem el) {
	node *p;
	p = (node*) malloc(sizeof(node));
	p->elem = el;
	if(l->head == NULL) {
		p->next = NULL;
		p->prev = NULL;
		p->v1 = NULL;
		p->v2 = NULL;
		l->head = p;
		l->tail = p;
	} else {
		l->tail->next = p;
		p->prev = l->tail;
		p->next = NULL;
		p->v1 = NULL;
		p->v2 = NULL;
		l->tail = p;
	}
	l->count++;
	return p;
}

node *insertBegin(list *l, type_elem el) {
	node *p;
	p = (node*) malloc(sizeof(node));
	p->elem = el;
	if(l->head == NULL) {
		l->head = p;
		l->tail = p;
		p->next = NULL;
		p->prev = NULL;
		p->v1 = NULL;
		p->v2 = NULL;
	} else {
		l->head->prev = p;
		p->prev = NULL;
		p->v1 = NULL;
		p->v2 = NULL;
		p->next = l->head;
		l->head = p;
	}
	l->count++;
	return p;
}

node *searchId(list *l, node *start, int id) {
	if (start == NULL) start = l->head;
	if (l->head == NULL) return NULL;
	if (start->elem.id == id) {
		return start;
	}
	if (start->next != NULL) {
		return searchId(l, start->next, id);
	} else {
		return NULL;
	}
}

type_elem removeNode(list *l, node *n) {
	type_elem aux = {0, 0, FALSE};

	if(n == NULL)
		return aux;
	aux = n->elem;	
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
	free(n);
	l->count--;
	return aux;
}

type_elem removeId(list *l, int id) {
	type_elem aux = {0, 0, FALSE};
	node *n;

	n = searchId(l, NULL, id);
	if(n == NULL)
		return aux;
	aux = n->elem;	
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
	free(n);
	l->count--;
	return aux;
}

type_elem removeFromEndOrBegin(list *l, char flag) {
	type_elem aux;
	node *p;

	if (flag == 'b') {
		aux = l->head->elem;
		p = l->head;
		if (l->head == l->tail) {
			l->head = NULL;
			l->tail = NULL;	
		} else {
			l->head = l->head->next;
		}
	} else if (flag == 'e') { 
		aux = l->tail->elem;
		p = l->tail;
		if (l->head == l->tail) {
			l->head = NULL;
			l->tail = NULL;
		} else {
			l->tail = l->tail->prev;
			l->tail->next = NULL;
		}
	}
	free(p);
	l->count--;
	return aux;
}

void printList(list *l, node *start, char orderby) {
	if (l->count == 0) return;
	if (orderby == 'a') {
		printf("%d\n", start->elem.id);
		if(start->next != NULL) {
			return printList(l, start->next, orderby);
		}
	}
	if (orderby == 'd') {
		printf("%d\n", start->elem.id);
		if(start->prev != NULL) {
			return printList(l, start->prev, orderby);
		}
	}
}