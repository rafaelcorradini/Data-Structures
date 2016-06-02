#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "graph.h"

int main() {

	list *l;
	int i, id, id2, idc, n, m, c, op, s;
	graph *g;
	node *v, *e, *z;
	type_elem el;
	double total = 9999999, totalj = 0, x, y, value;
	const type_elem emptyElem = {0, ' '};

	g = initGraph();

	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		el.id = i;
		el.c = FALSE;
		insertVertex(g, el);
	}
	scanf("%lf %lf", &x, &y);
	scanf("%d", &m);
	for (i = 1; i <= m; i++) {
		scanf("%d %d %lf", &id, &id2, &value);
		el.id = i;
		el.c = FALSE;
		el.value = value;
		insertEdge(g, id, id2, el);
	}
	scanf("%d", &c);
	for (i = 1; i <= c; i++) {
		scanf("%d", &idc);
		v = searchId(g->vertices, g->vertices->head, idc);
		setConsultor(g, v);
	}
	scanf("%d %d", &op, &s);
	
	z = searchId(g->vertices, g->vertices->head, s);
	bellmanford(g, z);
	totalj = g->vertices->head->elem.dist + y;
	for (v = g->vertices->head; v != NULL;) {
		if(v->elem.c == TRUE) {
			if(total > v->elem.dist) {
				total = v->elem.dist;
				z = v;
			}
		}
		v = v->next;
	}
	total = total + x;

	

	switch(op) {
		case 1: if(total > totalj) {
					printf("%.3lf", totalj);
				} else {
					printf("%.3lf", total);
				}
				break;

		case 2: if(total < totalj) {
					for (v = z; v != NULL;) {
						printf("%d ", v->elem.id);
						v = v->parent;
					}
				} else {
					for (v = g->vertices->head; v != NULL;) {
						printf("%d ", v->elem.id);
						v = v->parent;
					}
				}
				break;

		case 3: if(total < totalj) {
					printf("Repassa %.3lf", total);
				} else {
					printf("Atende %.3lf", totalj);
				}
				break;
	}

	printf("\n");
	eraseGraph(g);

	return 0;

}