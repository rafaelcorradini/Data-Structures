#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "map.h"

void printGraph(Graph *g, Map *map_vertices, Map *map_edges) {
	printf("%d\n", numVertices(g));
	printMap(map_vertices, 'v');
	printf("%d\n", numEdges(g));
	printMap(map_edges, 'e');
}

void printDistance(Graph *G, Map *map_vertices, double **D, int v, int w) {
	printf("%.3lf\n", D[v][w]);
}	

void printShortestPath(Graph *G, Map *map_vertices, int **P, int v, int w) {

	if (P[v][w] == 0) {
		printf("0\n");
		return;
	}

	do {
		if (v == P[v][w]) {
			printf("0\n");
			return;
		}
			
		printf("%d ", v);
		v = P[v][w];
	} while(v != w);

	printf("%d\n", w);
}	

void FloydWarshall(Graph *G, Map *map_vertices, Map *map_edges, double **D, int **P) {
    int i, j, k;
    Node *n;
 	
 	for (i = 0; i <= getLastMap(map_vertices); i++) {
		for (j = 0; j <= getLastMap(map_vertices); j++) {
			P[i][j] = 0;

			if(i == j)
				D[i][j] = 0;
			else
		 		D[i][j] = 1000000;
		}

	}

	distVector(map_edges, D, P);

    for (k = 0; k <= getLastMap(map_vertices); k++) {
        for (i = 0; i <= getLastMap(map_vertices); i++) {
            for (j = 0; j <= getLastMap(map_vertices); j++) {
                if ((D[i][k] + D[k][j] < D[i][j]) && (i != j) && (k != j) && (i != k)) {
                    D[i][j] = D[i][k] + D[k][j];
                    P[i][j] = P[i][k];
                }
            }
        }
    }
}

int main() {
	int ivalue, v1, v2, id, vid = 1, eid = 1, **P, j, k, t = -1;
	double dvalue, **D;
	char op[2];
	Graph *g;
	Map_elem melem;
	Map *map_vertices, *map_edges;
	Node *n;
	
	g = initGraph();
	map_vertices = define();
	map_edges = define();

	while(1) {
		dvalue = 0;
		ivalue = 0;
		scanf(" %c %c", &op[1], &op[2]);
		switch(op[1]) {
			case 'C': 	switch(op[2]) {
	                    	case 'V': scanf(" %d", &ivalue);
		                    		  n = insertVertex(g, ivalue);
									  melem.node = n;
									  melem.id = vid++;
									  insertMap(map_vertices, melem);
		                    		  break;

		                    case 'A': scanf(" %d %d %lf", &v1, &v2, &dvalue);
									  n = insertEdge(g, searchMap(map_vertices, v1).node, searchMap(map_vertices, v2).node, dvalue);
									  melem.node = n;
									  melem.id = eid++;
									  melem.v1 = v1;
									  melem.v2 = v2;
									  insertMap(map_edges, melem);
									  break;
	                  	}				
					  	break;	

			case 'D': 	switch(op[2]) {
		                    case 'V':   scanf(" %d", &id);
										ivalue = removeVertex(g, searchMap(map_vertices, id).node);
										removeEdgesMap(map_edges, id);
										removeMap(map_vertices, id);
										break;

		                    case 'A':	scanf(" %d", &id);
										dvalue = removeEdge(g, searchMap(map_edges, id).node);
										removeMap(map_edges, id);
										break;
	                  	}				
					  	break;

			case 'T': 	switch(op[2]) {
		                    case 'V':   scanf(" %d %d", &id, &ivalue);
										if (ivalue >= 0)
											replaceVertex(g, searchMap(map_vertices, id).node, ivalue);
										break;

		                    case 'A':	scanf(" %d %lf", &id, &dvalue);
										if (dvalue >= 0)
											replaceEdge(g, searchMap(map_edges, id).node, dvalue);
										break;
	                  	}				
					  	break;

			case 'F': 	switch(op[2]) {
							case 'W': if (t != -1) {
											for (j = 0; j <= t; j++) {
											  free(D[j]);
											  free(P[j]);
											}
											free(P);
											free(D);
										}
										

										t = getLastMap(map_vertices);

										D = (double**) malloc((t+1) * sizeof(double*));
										P = (int**) malloc((t+1) * sizeof(int*));
										for (j = 0; j <= t; j++) {
										 	D[j] = (double*) malloc((t+1) * sizeof(double));
										 	P[j] = (int*) malloc((t+1) * sizeof(int));
										}

										FloydWarshall(g, map_vertices, map_edges, D, P);
										break;
							case 'M': 	if (t != -1) {
											for (j = 0; j <= t; j++) {
											  free(D[j]);
											  free(P[j]);
											}
											free(P);
											free(D);
										}

										freeNodesMap(map_vertices);
										freeNodesMap(map_edges);
				    					free(map_vertices);
				    					free(map_edges); 
				    					freeGraph(g); 
				    				

										return 0;
						}
					  	break;

			case 'I': 	switch(op[2]) {
		                    case 'G':   printGraph(g, map_vertices, map_edges);
										break;

		                    case 'D':	scanf(" %d %d", &v1, &v2);
		                    			printDistance(g, map_vertices, D, v1, v2);
										break;

							case 'C':	scanf(" %d %d", &v1, &v2);
										if(D[v1][v2] == 1000000 || v1 == v2)
											printf("0\n");
										else
		                    				printShortestPath(g, map_vertices, P, v1, v2);
										break;
	                  	}				
					  	break;

			default: 	/*if (t != -1) {
							for (j = 0; j <= t; j++) {
							  free(D[j]);
							  free(P[j]);
							}
							free(P);
							free(D);
						}*/

						freeNodesMap(map_vertices);
						freeNodesMap(map_edges);
    					free(map_vertices);
    					free(map_edges); 
						freeGraph(g);

						
				 	 	return 0;

		}
	}
	return 0;

}