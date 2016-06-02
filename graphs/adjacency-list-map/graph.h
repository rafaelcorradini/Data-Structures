typedef struct graph Graph;

/* MÉTODOS QUE MODIFICAM O GRAFO */
/* Cria um grafo */
Graph *initGraph();

/* Apaga um grafo */
void eraseGraph(Graph* G);

/* Retorna a referência do vértice oposto a v na aresta e */
Node *opposite(Graph* G, v, e);

/* Retorna 1 (um) se os vértices v e w forem adjacentes ou 0 (zero) */
int areAdjacent(Graph* G, Node* v, Node* w);

/* substitui o elemento armazenado no vértice v por o */
void replaceVertex(Graph* G, Node* v, int o);

/* Função para substituir o elemento armazenado na aresta 'e' por 'o' */
void replaceEdge(Graph* G, Node* e, double o);

/* Função para adicionar um vértice ao grafo */
Node *insertVertex(Graph* G, int o);

/* Função para adicionar uma aresta ao grafo */
Node *insertEdge(Graph* G, Node* v, Node* w, double o);



/* Função para remover um vértice do grafo, returns a empty element when fail */
int removeVertex(Graph* G, node* v);

/* Função para remover uma aresta do grafo, returns a empty element when fail */
double removeEdge(Graph* G, node* e);

int vertexValue(Graph* G, node* v);

double edgeValue(Graph* G, node* e);

/* MÉTODOS GERAIS */
/* Função para acessar o número de vértices de um grafo */
int numVertices(Graph* G);

/* Função para acessar o número de arestas de um grafo */
int numEdges(Graph* G);

/* Função para acessar o grau de um vértice de um grafo */
int degree(Graph* G, node* v);


/* MÉTODOS DE IMPRESSÃO */
/* Imprime uma lista contendo o identificador e o valor de cada vértice */
// void printVertices(Graph* G);

/* Imprime uma lista contendo o identificador, os vértices e o valor de cada aresta */
// void printEdges(Graph* G);

/* Imprime o grafo */
// void printGraph(Graph* G);