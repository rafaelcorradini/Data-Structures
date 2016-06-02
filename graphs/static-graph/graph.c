#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

#define FALSE 0
#define TRUE 1

/* Vertex */
struct vertex {
    /* marcador que indica se o vértice está sendo usado (used == TRUE) ou não
    ** (used==FALSE) */
    int used;
    
    /* objeto armazenado pelo vértice */
	int value;
};

/* Edge */
struct edge {
    /* marcador que indica se a aresta está sendo usada (used == TRUE) ou não
    ** (used == FALSE) */
    int used;
    
    /* primeiro vértice da aresta */
    int v1;
    
    /* segundo vértice da aresta */
    int v2;
    
    /* objeto armazenado pela aresta */
    int value;
};

/* Graph
** implementado utilizando-se a estrutura: LISTA DE ARESTAS */
struct graph {
    /* vetor estático que armazena os vértices */
    Vertex vertices[MAX_VERTICES];
    
    /* vetor estático que armazena as arestas */
    Edge edges[MAX_EDGES];
    
    /* armazena o número de vértices e o número de arestas do grafo*/
    int n_vertices, n_edges;
};

Graph* createGraph(void) {
    int i, j;
    Graph* g;
    
    /* Aloca dinamicamente um grafo que é retornado para o usuário */
    g = (Graph*) malloc(sizeof(Graph));

    /* Marca todos os vértices como livres (i.e., não utilizadas) */
    for (i = 0; i < MAX_VERTICES; i++) { g->vertices[i].used = FALSE; }
    
    /* Marca todas as arestas como livres (i.e., não utilizadas) */
    for (j = 0; j < MAX_EDGES; j++) { g->edges[j].used = FALSE; }
    
    g->n_vertices = 0;
    g->n_edges = 0;
    
    return g;
}

/* Apaga um grafo */
void eraseGraph(Graph* g) {
    /* Libera o espaço em memória alocado pela função createGraph() */
    free(g);
}

/* Função para adicionar um vértice ao grafo, retorna o índice em que foi inserido o vertice */
int insertVertex(Graph* g, int o) {
    int i;
    
    for (i = 0; i < MAX_VERTICES; i++) {
        if (g->vertices[i].used == FALSE) break;
    }
    
    if (i < MAX_VERTICES) {
        g->n_vertices++;
        g->vertices[i].value = o;
        g->vertices[i].used = TRUE;
    }
    return i;
}

/* Função para adicionar uma aresta ao grafo */
void insertEdge(Graph* g, int v, int w, int o)  {
    int i;

    if (g->vertices[v].used == TRUE && g->vertices[v].used == TRUE) {
        for (i = 0; i < MAX_EDGES; i++) {
            if (g->edges[i].used == FALSE) break;
        }
        if (i < MAX_EDGES) {
            g->edges[i].value = o;
            g->edges[i].v1 = v;
            g->edges[i].v2 = w;
            g->edges[i].used = TRUE;
            g->n_edges++;
        }
    } 
    
}

/* Função para substituir o elemento armazenado no vértice 'v' por 'o' */
void replaceVertex(Graph* g, int v, int o) {
    g->vertices[v].value = o;
}

/* Função para substituir o elemento armazenado na aresta 'e' por 'o' */
void replaceEdge(Graph* g, int e, int o) {
    
    g->edges[e].value = o;
    
}

/* Função para remover um vértice do grafo */
void removeVertex(Graph* g, int v) {
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

/* Função para remover uma aresta do grafo */
void removeEdge(Graph* g, int e) {
    g->edges[e].used = FALSE;
    g->n_edges--;
}


/* MÉTODOS GERAIS */
/* Função para acessar o número de vértices de um grafo */
int numVertices(Graph* g) {
    
    return g->n_vertices;
    
}

/* Função para acessar o número de arestas de um grafo */
int numEdges(Graph* g) {
    return g->n_edges;
}

/* Função para acessar o grau de um vértice de um grafo */
int degree(Graph* g, int v) {
    int i, c = 0;

    for (i = 0; i < MAX_EDGES; i++) {
        if ((g->edges[i].v1 == v || g->edges[i].v2 == v) && g->edges[i].used == TRUE) {
	     c++;
	     if (g->edges[i].v1 == g->edges[i].v2 && g->edges[i].used == TRUE) c++;
	}
    }
    return c;
    
}

/* Função para verificar se dois vértices são ou não adjacentes */
int areAdjacent(Graph* g, int v, int w) {
    
    int i, c = 0;
	
    for (i = 0; i < MAX_EDGES; i++) {
        if (((g->edges[i].v1 == v && g->edges[i].v2 == w) || (g->edges[i].v2 == v && g->edges[i].v1 == w)) && g->edges[i].used == TRUE) break;
    }
    if (i < MAX_EDGES) return TRUE;
    else return FALSE;
    
}


/* MÉTODOS DE IMPRESSÃO */
/* Imprime uma lista contendo o identificador e o valor de cada vértice */
void printVertices(Graph* g) {
    int i, num_vertices;
    
    num_vertices = numVertices(g);
    printf("%d\n", num_vertices);
    
    for (i = 0; i < MAX_VERTICES; i++) {
        if (g->vertices[i].used == TRUE)
            printf("%d %d\n", i, g->vertices[i].value);
    }
}

/* Imprime uma lista contendo o identificador, os vértices e o valor de cada aresta */
void printEdges(Graph* g) {
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

/* Imprime o grafo */
void printGraph(Graph* g) {
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

/* Imprime uma lista contendo o grau de cada vértice */
void printDegree(Graph* g) {
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

/* Imprime TRUE se dois vértices são adjacentes ou FALSE caso contrário */
void printAdjacent(Graph* g, int v, int w) {
    if (areAdjacent(g, v, w)) printf("TRUE\n");
    else printf("FALSE\n");
}

Graph* createMazeGraph(int matriz[MAX_MAZE][MAX_MAZE], int n, int m) {
    int i, j;
    Graph* g;

    g = createGraph();

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
int bfs(Graph* g, int v, int end) {
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