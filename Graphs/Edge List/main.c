#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "graph.h"

int main() {
	list *l;
	int i, id, v1, v2;
	graph *g;
	type_elem el;
	const type_elem emptyElem = {0, ' '};

	g = initGraph();

	while(1) {
		printf("1 - Insert vertex\n");
		printf("2 - Insert Edge\n");
		printf("3 - Remove Vertex\n");
		printf("4 - Remove Edge\n");
		printf("5 - Print Graph\n");
		scanf(" %d", &i);
		id = 0;
		switch(i) {
			case 1: printf("\nid: ");
					scanf(" %d", &id);
					el.id = id;
					insertVertex(g, el);
					break;

			case 2: printf("\nid: ");
					scanf(" %d", &id);
					printf("\nv1: ");
					scanf(" %d", &v1);
					printf("\nv2: ");
					scanf(" %d", &v2);
					el.id = id;
					insertEdge(g, v1, v2, el);
					break;

			case 3: printf("\nid: ");
					scanf(" %d", &id);
					el = removeVertex(g, id);
					if (el.id == 0)
						printf("Vertex not found\n");
					break;

			case 4: printf("\nid: ");
					scanf(" %d", &id);
					el = removeEdge(g, id);
					if (el.id == 0)
						printf("Edge not found\n");
					break;

			case 5: printf("-------\n");
					printGraph(g);
					printf("-------\n");
					break;

			default: eraseGraph(g); 
					 exit(1);

		}
	}
	return 0;

}