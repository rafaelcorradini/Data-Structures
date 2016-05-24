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

node *insertPriority(list *l, type_elem el) {
	node *p, *v;
	int dist;
	
	p = (node*) malloc(sizeof(node));
	p->elem = el;

	if(l->head == NULL) {
		p->next = NULL;
		p->prev = NULL;
		l->head = p;
		l->tail = p;
	} else {
		v = l->head;
		dist = v->elem.dist;
		while (p->elem.dist > dist) {
			if (v == NULL)
				break;
			dist = v->elem.dist;
			v = v->next;
		}
		if (v == NULL) {
			l->tail->next = p;
			p->prev = l->tail;
			p->next = NULL;
			l->tail = p;
		} else if (v == l->head){
			v->prev = p;
			p->next = v;
			p->prev = NULL;
			l->head = p;
		} else {
			p->prev = v->prev;
			v->prev->next = p;
			v->prev = p;
			p->next = v;
		}
	}
	p->v1 = NULL;
	p->v2 = NULL;
	p->parent = NULL;
	p->type = 'v';
	l->count++;
	return p;
}

node *insertPriorityId(list *l, type_elem el) {
	node *p, *v;
	int id;

	p = (node*) malloc(sizeof(node));
	p->elem = el;

	if(l->head == NULL) {
		p->next = NULL;
		p->prev = NULL;
		l->head = p;
		l->tail = p;
	} else {
		v = l->head;
		id = v->elem.id;
		while (p->elem.id > id) {
			if (v == NULL)
				break;
			id = v->elem.id;
			v = v->next;
		}
		if (v == NULL) {
			l->tail->next = p;
			p->prev = l->tail;
			p->next = NULL;
			l->tail = p;
		} else if (v == l->head) {
			l->head->prev = p;
			p->next = l->head;
			p->prev = NULL;
			l->head = p;
		} else {
			p->prev = v->prev;
			v->prev->next = p;
			v->prev = p;
			p->next = v;
		}
	}
	p->v1 = NULL;
	p->v2 = NULL;
	p->parent = NULL;
	p->type = 'v';
	l->count++;
	return p;
}

void replacePriority(list *l, node *n, type_elem el) {
	removeNode(l, n);
	insertPriority(l, el);
}

void eraseList(list *l, node *n) {
	if(l->head == NULL || n == NULL) {
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
		l->head = p;
		l->tail = p;
	} else {
		l->tail->next = p;
		p->prev = l->tail;
		p->next = NULL;
		l->tail = p;
	}
	p->v1 = NULL;
	p->v2 = NULL;
	p->parent = NULL;
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
	} else {
		l->head->prev = p;
		p->prev = NULL;
		p->next = l->head;
		l->head = p;
	}
	p->v1 = NULL;
	p->v2 = NULL;
	p->parent = NULL;
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
	type_elem aux = {0,0,0, FALSE};

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
	type_elem aux = {0,0,0, FALSE};
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
	type_elem aux = {0,0,0, FALSE};
	node *p;

	if (l->head == NULL)
		return aux;
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
		printf("%d %lf %lf\n", start->elem.id, start->elem.longitude, start->elem.latitude);
		if(start->next != NULL) {
			return printList(l, start->next, orderby);
		}
	}
	if (orderby == 'd') {
		printf("%d %lf %lf\n", start->elem.id, start->elem.longitude, start->elem.latitude);
		if(start->prev != NULL) {
			return printList(l, start->prev, orderby);
		}
	}
}