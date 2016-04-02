#ifndef _GRAPH_H_
#define _GRAPH_H_

#define MAX_VERTICES 20
#define MAX_EDGES 100
#define MAX_MAZE 15 // tamanho máximo do labarinto

#ifdef __cplusplus
extern "C" {
#endif

/* TADs */
/* Vertex */
typedef struct vertex Vertex;

/* Edge */
typedef struct edge Edge;

/* Graph */
typedef struct graph Graph;


/* MÉTODOS QUE MODIFICAM O GRAFO */
/* Cria um grafo */
Graph* createGraph(void);

/* Apaga um grafo */
void eraseGraph(Graph* g);

/* Função para adicionar um vértice ao grafo */
int insertVertex(Graph* g, int o);

/* Função para adicionar uma aresta ao grafo */
void insertEdge(Graph* g, int v, int w, int o);

/* Função para substituir o elemento armazenado no vértice 'v' por 'o' */
void replaceVertex(Graph* g, int v, int o);

/* Função para substituir o elemento armazenado na aresta 'e' por 'o' */
void replaceEdge(Graph* g, int e, int o);

/* Função para remover um vértice do grafo */
void removeVertex(Graph* g, int v);

/* Função para remover uma aresta do grafo */
void removeEdge(Graph* g, int e);


/* MÉTODOS GERAIS */
/* Função para acessar o número de vértices de um grafo */
int numVertices(Graph* g);

/* Função para acessar o número de arestas de um grafo */
int numEdges(Graph* g);

/* Função para acessar o grau de um vértice de um grafo */
int degree(Graph* g, int v);

/* Função para verificar se dois vértices são ou não adjacentes */
int areAdjacent(Graph* g, int v, int w);


/* MÉTODOS DE IMPRESSÃO */
/* Imprime uma lista contendo o identificador e o valor de cada vértice */
void printVertices(Graph* g);

/* Imprime uma lista contendo o identificador, os vértices e o valor de cada aresta */
void printEdges(Graph* g);

/* Imprime o grafo */
void printGraph(Graph* g);

/* Imprime uma lista contendo o grau de cada vértice */
void printDegree(Graph* g);

/* Imprime TRUE caso os dois vértices sejam adjacentes ou FALSE caso contrário */
void printAdjacent(Graph* g, int v, int w);

Graph* createMazeGraph(int matriz[MAX_MAZE][MAX_MAZE], int n, int m);

int bfs(Graph* g, int v, int end);

void enqueue(int q[MAX_VERTICES], int v);

int dequeue(int q[MAX_VERTICES]);

int empty(int q[MAX_VERTICES]);

void initQueue(int q[MAX_VERTICES]);

#ifdef __cplusplus
}
#endif

#endif /*_GRAPH_H_*/

