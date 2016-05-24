typedef struct {
	list *vertices;
	list *edges;
} graph;


/* MÉTODOS QUE MODIFICAM O GRAFO */
/* Cria um grafo */
graph *initGraph();

/* Apaga um grafo */
void eraseGraph(graph* g);

/* Função para adicionar um vértice ao grafo */
node *insertVertex(graph* g, type_elem el);

/* Função para adicionar uma aresta ao grafo */
node *insertEdge(graph* g, int v, int w, type_elem el);

/* Função para substituir o elemento armazenado no vértice 'v' por 'o' */
void replaceVertex(graph* g, int v, type_elem el);

/* Função para substituir o elemento armazenado na aresta 'e' por 'o' */
void replaceEdge(graph* g, int e, type_elem el);

/* Função para remover um vértice do grafo, returns a empty element when fail */
type_elem removeVertex(graph* g, int v);

/* Função para remover uma aresta do grafo, returns a empty element when fail */
type_elem removeEdge(graph* g, int e);


/* MÉTODOS GERAIS */
/* Função para acessar o número de vértices de um grafo */
int numVertices(graph* g);

/* Função para acessar o número de arestas de um grafo */
int numEdges(graph* g);

/* Função para acessar o grau de um vértice de um grafo */
int degree(graph* g, int v);

/* Função para verificar se dois vértices são ou não adjacentes */
boolean areAdjacent(graph* g, int v, int w);


/* MÉTODOS DE IMPRESSÃO */
/* Imprime uma lista contendo o identificador e o valor de cada vértice */
void printVertices(graph* g);

/* Imprime uma lista contendo o identificador, os vértices e o valor de cada aresta */
void printEdges(graph* g);

/* Imprime o grafo */
void printGraph(graph* g);