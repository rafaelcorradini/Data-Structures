typedef struct graph Graph;
typedef struct list_node Node;

// Cria um grafo
Graph *initGraph();

// Apaga um grafo
void freeGraph(Graph *G);

// Retorna a referência do vértice oposto a v na aresta e
Node *opposite(Graph *G, Node* v, Node* e);

// Retorna 1 (um) se os vértices v e w forem adjacentes ou 0 (zero)
int areAdjacent(Graph *G, Node* v, Node* w);

// substitui o elemento armazenado no vértice v por o
void replaceVertex(Graph *G, Node* v, int o);

// Função para substituir o elemento armazenado na aresta 'e' por 'o'
void replaceEdge(Graph *G, Node* e, double o);

// Função para adicionar um vértice ao grafo
Node *insertVertex(Graph *G, int o);

// Função para adicionar uma aresta ao grafo
Node *insertEdge(Graph *G, Node* v, Node* w, double o);

// Função para remover um vértice do grafo, returns a empty element when fail
int removeVertex(Graph *G, Node* v);

// Função para remover uma aresta do grafo, returns a empty element when fail
double removeEdge(Graph *G, Node* e);

// Função que retorna o valor armazenado no vértice
int vertexValue(Graph *G, Node* v);

// Função que retorna o valor armazenado na aresta
double edgeValue(Graph *G, Node* e);

// Função para acessar o número de vértices de um grafo
int numVertices(Graph *G);

// Função para acessar o número de arestas de um grafo
int numEdges(Graph *G);