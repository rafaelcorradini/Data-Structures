#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "graph.h"

int main() {
	int i, n, op;
	graph *g;
	type_elem el;

	g = initGraph();

	scanf("%d", &n);
	for (i = 0; i < n; ++i) {
		scanf("%d %lf %lf", &el.id, &el.longitude, &el.latitude);
		insertVertex(g, el);
	}
	scanf("%d", &op);
	// função que deixa o grafo completamente conexo
	makeGraphConnectivity(g, g->vertices->head);
	primJarnik(g);
	
	
	if (op == 1) {
		printCities(g);
	}

	if (op == 2) {
		printf("%.3lf\n", totalCities(g));
	}

	eraseGraph(g);

	return 0;
}