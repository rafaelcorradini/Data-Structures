#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "graph.h"

int main() {
	list *l;
	int i, value, v1, v2, id;
	Graph *g;

	g = initGraph();

	while(1) {
		printf("1 - Insert vertex\n");
		printf("2 - Insert Edge\n");
		printf("3 - Remove Vertex\n");
		printf("4 - Remove Edge\n");
		printf("5 - Print Graph\n");
		scanf(" %d", &i);
		value = 0;
		switch(i) {
			case 1: printf("\nvalue: ");
					scanf(" %d", &value);
					insertVertex(g, value);
					break;

			case 2: printf("\nvalue: ");
					scanf(" %d", &value);
					printf("\nv1: ");
					scanf(" %d", &v1);
					printf("\nv2: ");
					scanf(" %d", &v2);
					insertEdge(g, find(g->vertices, v1), find(g->vertices, v2), value);
					break;

			case 3: printf("\nid: ");
					scanf(" %d", &id);
					value = removeVertex(g, find(g->vertices, id));
					if (value < 0)
						printf("Vertex not found\n");
					break;

			case 4: printf("\nvid: ");
					scanf(" %d", &id);
					value = removeEdge(g, find(g->edges, id));
					if (value < 0)
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