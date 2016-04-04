typedef struct {
	list *vertices;
	list *edges;
} graph;

typedef struct {
	list *vertices;
	list *edges;
} vertices;


/* MÉTODOS QUE MODIFICAM O GRAFO */
/* Cria um grafo */
graph* createGraph(void);

/* Apaga um grafo */
void eraseGraph(graph* g);

/* Função para adicionar um vértice ao grafo */
int insertVertex(graph* g, int o);

/* Função para adicionar uma aresta ao grafo */
void insertEdge(graph* g, int v, int w, int o);

/* Função para substituir o elemento armazenado no vértice 'v' por 'o' */
void replaceVertex(graph* g, int v, int o);

/* Função para substituir o elemento armazenado na aresta 'e' por 'o' */
void replaceEdge(graph* g, int e, int o);

/* Função para remover um vértice do grafo */
void removeVertex(graph* g, int v);

/* Função para remover uma aresta do grafo */
void removeEdge(graph* g, int e);


/* MÉTODOS GERAIS */
/* Função para acessar o número de vértices de um grafo */
int numVertices(graph* g);

/* Função para acessar o número de arestas de um grafo */
int numEdges(graph* g);

/* Função para acessar o grau de um vértice de um grafo */
int degree(graph* g, int v);

/* Função para verificar se dois vértices são ou não adjacentes */
int areAdjacent(graph* g, int v, int w);


/* MÉTODOS DE IMPRESSÃO */
/* Imprime uma lista contendo o identificador e o valor de cada vértice */
void printVertices(graph* g);

/* Imprime uma lista contendo o identificador, os vértices e o valor de cada aresta */
void printEdges(graph* g);

/* Imprime o grafo */
void printGraph(graph* g);

/* Imprime uma lista contendo o grau de cada vértice */
void printDegree(graph* g);

/* Imprime TRUE caso os dois vértices sejam adjacentes ou FALSE caso contrário */
void printAdjacent(graph* g, int v, int w);

graph* createMazeGraph(int matriz[MAX_MAZE][MAX_MAZE], int n, int m);

int bfs(graph* g, int v, int end);