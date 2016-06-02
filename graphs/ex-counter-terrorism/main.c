#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "graph.h"

int main() {

	list *l;
	int i, id, id2, n, m, op, a, aux;
	graph *g;
	node *v, *e, *z;
	type_elem el;
	const type_elem emptyElem = {0, 0, FALSE};

	g = initGraph();

	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		el.id = i;
		insertVertex(g, el);
	}
	scanf("%d", &m);
	for (i = 1; i <= m; i++) {
		scanf("%d %d", &id, &id2);
		el.id = i;
		insertEdge(g, id, id2, el);
	}

	scanf("%d", &op);
	kcore(g);
	
	switch(op) {
		case 1: for (v = g->vertices->head; v != NULL;) {
			        if(v->elem.coreness > aux) {
			        	aux = v->elem.coreness;
			        }
			        v = v->next;
			    }
			    printf("%d\n", aux);

			    for (v = g->vertices->head; v != NULL;) {
			        if(v->elem.coreness == aux) {
			        	printf("%d ", v->elem.id);
			        }
			        v = v->next;
			    }
				break;

		case 2: for (v = g->vertices->head; v != NULL;) {
			        printf("%d ", v->elem.coreness);
			        v = v->next;
			    }
				break;
	}

	printf("\n");
	eraseGraph(g);

	return 0;

}