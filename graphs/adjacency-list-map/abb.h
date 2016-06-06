typedef struct list_node Node;
typedef struct {
	int id;
	Node *node;
	int v1;
	int v2;

} Map_elem;

struct abb_node {
	Map_elem elem;
	struct abb_node *leftChild, *rightChild, *parent;
};
typedef struct abb_node map_node;

typedef struct {
	int nelem;
	map_node *root;
	int lastId;
} Map;

typedef enum { FALSE, TRUE } boolean;

// inicializa a arvore e retorna ela mesma
Map *defineABB(); 

// retorna 1 se arvore estiver vazia e 0 se nao estiver
boolean isEmpty(Map *T); 

// devolve a raíz da árvore
map_node *root(Map *T); 

// insere um elemento na arvore retorna o nodo no qual foi inserido, NULL se falhar
map_node *insertElem(Map *T, Map_elem el); 

// inicia uma pesqusia a partir do nodo n, se estiver vazia retorna NULL
map_node *searchElem(Map *T, int id, map_node *n); 

boolean expandExternal(Map *T, map_node *n);

// verifica se n um no externo
boolean isExternal(map_node *n); 

// retorna o no irmao de n
map_node *sibling(map_node *n); 

// remove um no externo
Map_elem removeAboveExternal(Map *T, map_node *n); 

// substitui o elem de n por el e retorna n ou NULL
map_node *replaceElem(Map_elem el, map_node *n);

// remove o no de chave k se existir
Map_elem removeElem(Map *T, int id); 

//coloca todas as distancias na matriz D
void distVectorAux(Map *T, double **D, map_node *n); 

// encontra um substituto para um no interno, para que se possa efetuar sua remocao
map_node *substitute(Map *T, map_node *n); 

// percurso inter-fixado
void printABB(Map *T, map_node *n, char op); 

// desalocar todos os nós da ABB
void freeNodes(Map *T, map_node *n); 

// retorna o maior Id da árvore
int getLastAbb(Map *T);
