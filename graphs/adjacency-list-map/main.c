#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "map.h"

void printGraph(Graph *g, Map *map_vertices, Map *map_edges) {
	printf("n\n");
	printMap(map_vertices, 'v');
	printf("m\n");
	printMap(map_edges, 'e');
}

void printDistance(Graph *G, Map *map_vertices, double **D, int v, int w) {
	printf("%.3lf", D[v][w]);
}	

void printShortestPath(Graph *G, Map *map_vertices, int **P, int v, int w) {
	do {
		printf("%d ", w);
		w = P[v][w];
	} while(w != v);

	printf("%d", v);
}	

void FloydWarshall(Graph *G, Map *map_vertices, Map *map_edges, double **D, int **P) {
    int i, j, k;
    Node *n;
 	
 	for (i = 0; i <= getLastMap(map_vertices); i++) {
		for (j = 0; j <= getLastMap(map_vertices); j++) {
			if(i == j)
				D[i][j] == 0;
			else
		 		D[i][j] = 1000000;
		}

	}

	distVector(map_edges, D);

    for (k = 0; k <= getLastMap(map_vertices); k++) {
        for (i = 0; i <= getLastMap(map_vertices); i++) {
            for (j = 0; j <= getLastMap(map_vertices); j++) {
                if (D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = P[k][j];
                }
            }
        }
    }
}

int main() {
	int i, ivalue, v1, v2, id, vid = 1, eid = 1, **P, j, k;
	double dvalue, **D;
	Graph *g;
	Map_elem melem;
	Map *map_vertices, *map_edges;
	Node *n;
	
	g = initGraph();
	map_vertices = define();
	map_edges = define();

	while(1) {
		printf("1 - Insert vertex\n");
		printf("2 - Insert Edge\n");
		printf("3 - Remove Vertex\n");
		printf("4 - Remove Edge\n");
		printf("5 - Print Graph\n");
		scanf(" %d", &i);
		dvalue = 0;
		ivalue = 0;
		switch(i) {
			case 1: printf("\nvalue: ");
					scanf(" %d", &ivalue);
					n = insertVertex(g, ivalue);
					melem.node = n;
					melem.id = vid++;
					insertMap(map_vertices, melem);
					break;

			case 2: printf("\nvalue: ");
					scanf(" %lf", &dvalue);
					printf("\nv1: ");
					scanf(" %d", &v1);
					printf("\nv2: ");
					scanf(" %d", &v2);
					n = insertEdge(g, searchMap(map_vertices, v1).node, searchMap(map_vertices, v2).node, dvalue);
					melem.node = n;
					melem.id = eid++;
					melem.v1 = v1;
					melem.v2 = v2;
					insertMap(map_edges, melem);
					break;

			case 3: printf("\nid: ");
					scanf(" %d", &id);
					ivalue = removeVertex(g, searchMap(map_vertices, id).node);
					if (ivalue < 0)
						printf("Vertex not found\n");
					else
						removeMap(map_vertices, id);
					break;

			case 4: printf("\nid: ");
					scanf(" %d", &id);
					dvalue = removeEdge(g, searchMap(map_edges, id).node);
					if (dvalue < 0)
						printf("Edge not found\n");
					else
						removeMap(map_edges, id);
					break;

			case 5: printf("-------\n");
					printGraph(g, map_vertices, map_edges);
					
					printf("-------\n");
					break;

			case 6:	D = (double**) malloc((getLastMap(map_vertices)+1) * sizeof(double*));

					P = (int**) malloc((getLastMap(map_vertices)+1) * sizeof(int*));

					for (j = 0; j <= getLastMap(map_vertices); j++) {
					 	D[j] = (double*) malloc((getLastMap(map_vertices)+1) * sizeof(double));
					 	P[j] = (int*) malloc((getLastMap(map_vertices)+1) * sizeof(int));
					}

					FloydWarshall(g, map_vertices, map_edges, D, P);
					printf("----\n");
					for (k = 0; k <= getLastMap(map_vertices); k++) {
						for (j = 0; j <= getLastMap(map_vertices); j++) {
						 	printf("%.3lf ", D[k][j]);
						}
						printf("\n");
					}
					printf("----\n");

					printDistance(g, map_vertices, D, 1, 2);
					printf("----\n");

					// for (j = 0; j <= (getLastMap(map_vertices); j++) {
					//   free(D[j]);
					// }
					// free(D);
					break;

			default: // freeGraph(g); 
				 	 exit(1);

		}
	}
	return 0;

}