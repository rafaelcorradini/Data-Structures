#include <stdio.h>
#include "graph.h"

int main(void) {
    int matriz[MAX_MAZE][MAX_MAZE], n, m, i, j, c, begin, end;
    Graph* grafo;
    
    
    
    scanf("%d", &n);
    scanf("%d", &m);
    for(i = 0; i < n; ++i) {
    	for (j = 0; j < m; ++j) {
    		scanf("%d ", &matriz[i][j]);
    	}
    }
    scanf("%d", &begin);
    scanf("%d", &end);

    grafo = createMazeGraph(matriz, n, m);

    c = bfs(grafo, begin, end);
    if(c>0) {
    	printf("%d\n", c);
    } else {
    	printf("NO EXIT\n");
    }
    
    
	eraseGraph(grafo);
	
	return 0;
}
