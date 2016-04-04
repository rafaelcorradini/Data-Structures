#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "list.h"

#define FALSE 0
#define TRUE 1

graph* initGraph(void) {
    graph* g;
    
    g = malloc(sizeof(graph));
    g->vertices = malloc(sizeof(list));
    g->edges = malloc(sizeof(list));
    
    return g;
}

void eraseGraph(graph* g) {
    eraseList(g->vertices);
    eraseList(g->edges);
    free(g);
}

int insertVertex(graph* g, type_elem el) {
    return insert(g->vertices, el);
}

void insertEdge(graph* g, int v, int w, type_elem el)  {
    // aqui
    return insert(g->edges, el);
}

void replaceVertex(graph* g, int v, int o) {
    g->vertices[v].value = o;
}

void replaceEdge(graph* g, int e, int o) {
    
    g->edges[e].value = o;
    
}

void removeVertex(graph* g, int v) {
    int i = 0;

    g->vertices[v].used = FALSE;
    for (i = 0; i < MAX_EDGES; i++) {
        if ((g->edges[i].v1 == v || g->edges[i].v2 == v) && g->edges[i].used == TRUE) {
	     g->edges[i].used = FALSE;
	     g->n_edges--;
	}
    }
    g->n_vertices--;
    
}

void removeEdge(graph* g, int e) {
    g->edges[e].used = FALSE;
    g->n_edges--;
}


int numVertices(graph* g) {
    
    return g->n_vertices;
    
}

int numEdges(graph* g) {
    return g->n_edges;
}


int degree(graph* g, int v) {
    int i, c = 0;

    for (i = 0; i < MAX_EDGES; i++) {
        if ((g->edges[i].v1 == v || g->edges[i].v2 == v) && g->edges[i].used == TRUE) {
	     c++;
	     if (g->edges[i].v1 == g->edges[i].v2 && g->edges[i].used == TRUE) c++;
	}
    }
    return c;
    
}


int areAdjacent(graph* g, int v, int w) {
    
    int i, c = 0;
	
    for (i = 0; i < MAX_EDGES; i++) {
        if (((g->edges[i].v1 == v && g->edges[i].v2 == w) || (g->edges[i].v2 == v && g->edges[i].v1 == w)) && g->edges[i].used == TRUE) break;
    }
    if (i < MAX_EDGES) return TRUE;
    else return FALSE;
    
}


void printVertices(graph* g) {
    int i, num_vertices;
    
    num_vertices = numVertices(g);
    printf("%d\n", num_vertices);
    
    for (i = 0; i < MAX_VERTICES; i++) {
        if (g->vertices[i].used == TRUE)
            printf("%d %d\n", i, g->vertices[i].value);
    }
}

void printEdges(graph* g) {
    int j, num_edges;
    
    num_edges = numEdges(g);
    printf("%d\n", num_edges);
    
    for (j = 0; j < MAX_EDGES; j++) {
        if (g->edges[j].used == TRUE) {
            if (g->edges[j].v1 > g->edges[j].v2) {
                printf("%d %d %d %d\n", j, g->edges[j].v2, g->edges[j].v1, g->edges[j].value);
            } else {
                printf("%d %d %d %d\n", j, g->edges[j].v1, g->edges[j].v2, g->edges[j].value);
            }
        }
    }
}

void printGraph(graph* g) {
    int i, j, num_vertices, num_edges;
    
    num_edges = numEdges(g);
    num_vertices = numVertices(g);
    printf("%d\n%d\n", num_vertices, num_edges);
    
    for (i = 0; i < MAX_VERTICES; i++) {
        if (g->vertices[i].used == TRUE)
            printf("%d %d\n", i, g->vertices[i].value);
    }
    
    for (j = 0; j < MAX_EDGES; j++) {
        if (g->edges[j].used == TRUE) {
            if (g->edges[j].v1 > g->edges[j].v2) {
                printf("%d %d %d %d\n", j, g->edges[j].v2, g->edges[j].v1, g->edges[j].value);
            } else {
                printf("%d %d %d %d\n", j, g->edges[j].v1, g->edges[j].v2, g->edges[j].value);
            }
        }
    }
}

void printDegree(graph* g) {
    int i, dg, num_vertices;
    
    num_vertices = numVertices(g);
    printf("%d\n", num_vertices);
    
    for (i = 0; i < MAX_VERTICES; i++) {
        if (g->vertices[i].used == TRUE) {
            dg = degree(g, i);
            printf("%d %d\n", i, dg);
        }
    }
}

void printAdjacent(graph* g, int v, int w) {
    if (areAdjacent(g, v, w)) printf("TRUE\n");
    else printf("FALSE\n");
}

graph* createMazeGraph(int matriz[MAX_MAZE][MAX_MAZE], int n, int m) {
    int i, j;
    graph* g;

    g = initGraph();

    for (i = 0; i < n; ++i) {
        for (j = 0; j < m; ++j) {
            
            if(matriz[i][j] != 0) {
                insertVertex(g, 1);
                matriz[i][j] = -1;
            } else {
                matriz[i][j] = insertVertex(g, 1);
            }


            if(j > 0 && matriz[i][j-1] != -1 && matriz[i][j] != -1)
                insertEdge(g, matriz[i][j], matriz[i][j-1], 0);

            if(i > 0 && matriz[i-1][j] != -1 && matriz[i][j] != -1)
                insertEdge(g, matriz[i][j], matriz[i-1][j], 0);  
            
        }
    }

    return g;
}

// busca em largura, retorna o tamanho do caminho mínimo
int bfs(graph* g, int v, int end) {
    int q[MAX_VERTICES]; // fila inicializada com todos os indices iguais a -1
    int i, w, begin, flag[MAX_VERTICES], c = 0, parent[MAX_VERTICES]; // flag: 0 - nao descoberto, 1 - descoberto, 2 - processado.  

    if(v == end) return 0;

    // flag e parent iniclizam com 0 em todos os índices
    for (i = 0; i < MAX_VERTICES; ++i) {
        flag[i] = 0;
        parent[i] = -1;
    }

    begin = v;

    initQueue(q);
    enqueue(q, v);
    flag[v] = 1;
    while(empty(q) == FALSE || v != end) { // se encontrar o menor caminho termina a busca
        v = dequeue(q);
        if(v == -1) break;

        flag[v] = 2;
        for (i = 0; i < MAX_EDGES; i++) {
            if ((g->edges[i].v1 == v || g->edges[i].v2 == v) && g->edges[i].used == TRUE) {
                if (g->edges[i].v1 == v) 
                    w = g->edges[i].v2;
                else
                    w = g->edges[i].v1;


                if(flag[w] == 0) {
                    enqueue(q, w);
                    parent[w] = v;
                    flag[w] = 1;
                }
            }
        }  
    }

    // calcula um caminho mínimo
    i = end;
    c++;
    while(parent[i] != begin) {
        if(parent[i] == -1) {
            return 0;
        }
        
        i = parent[i];
        c++;
        
    }

    return c;

}

void initQueue(int q[MAX_VERTICES]) {
    int i;
    for (i = 0; i < MAX_VERTICES; ++i) {
        q[i] = -1;
    }
}

// Usado em bfs para a manipulacão de uma fila estática
void enqueue(int q[MAX_VERTICES], int v) {
    int i;
    for (i = 0; i < MAX_VERTICES; ++i) {
        if(q[i] == -1) break;
    }
    q[i] = v;
}

// Usado em bfs para a manipulacão de uma fila estática
int dequeue(int q[MAX_VERTICES]) {
    int i, ret = -1;

    if(empty(q) == FALSE) {
        ret = q[0];
        q[0] = -1;
        for (i = 1; i < MAX_VERTICES; ++i) {
            if(q[i] != -1) {
                q[i-1] = q[i];  
            } else {
                q[i-1] = -1;
                break;
            }
        }
        
    } 

    return ret; 
}

// Usado em bfs para a manipulacão de uma fila estática
int empty(int q[MAX_VERTICES]) {
    if(q[0] == -1) 
        return TRUE;
    else
        return FALSE;
}