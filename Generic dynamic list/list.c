#include<stdio.h>
#include<stdlib.h>
#include"list.h"

#define FALSE 0
#define TRUE 1

list *initList() {
	list *l;
	l = malloc(sizeof(list));
	l->head = NULL;
	l->tail = NULL;
	l->count = 0;
	return l;
}

void eraseList(list *l, node *n) {
	if(n->next != NULL)
		eraseList(l, n->next);

	free(n->next);

	if(n == l->head)
		free(l);
}

int insert(list *l, type_elem el) {
	node *p;
	p = malloc(sizeof(node));
	p->elem = el;
	if(l->head == NULL) {
		l->head = p;
		l->tail = p;
		p->next = NULL;
		p->prev = NULL;
	} else {
		l->tail->next = p;
		p->prev = l->tail;
		p->next = NULL;
		l->tail = p;
	}
	l->count++;
	return TRUE;
}

int insertBegin(list *l, type_elem el) {
	node *p;
	p = malloc(sizeof(node));

	p->elem = el;
	if(l->head == NULL) {
		l->head = p;
		l->tail = p;
		p->next = NULL;
		p->prev = NULL;
	} else {
		l->head->prev = p;
		p->prev = NULL;
		p->next = l->head;
		l->head = p;
	}
	l->count++;
	return 1;
}

node *searchId(list *l, node *start, int id) {
	if (start == NULL) start = l->head;

	if (start->elem.id == id) {
		return start;
	}
	if (start->next != NULL) {
		return searchId(l, start->next, id);
	} else {
		return NULL;
	}
}


type_elem remove(list *l, node *n) {
	type_elem aux;
	
	aux = n->elem;
	free(n);
	l->count--;
	return aux;
}

type_elem removeId(list *l, int id) {
	type_elem aux;
	node *n;

	n = searchId(l, NULL, id);
	aux = n->elem;
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