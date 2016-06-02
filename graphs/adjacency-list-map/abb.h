typedef struct {
	int id;
	Node *node;
} tipo_elem;

struct abb_node {
	tipo_elem elem;
	struct abb_node *leftChild, *rightChild, *parent;
};
typedef struct abb_node map_node;

typedef struct {
	int nelem;
	map_node *root;
} abb;

typedef enum { FALSE, TRUE } boolean;

abb *defineABB(); // inicializa a arvore e retorna ela mesma

boolean isEmpty(abb *T); // retorna 1 se arvore estiver vazia e 0 se nao estiver

map_node *insertElem(abb *T, tipo_elem el); // insere um elemento na arvore retorna o nodo no qual foi inserido, NULL se falhar

map_node *searchElem(abb *T, int id, map_node *n); // inicia uma pesqusia a partir do nodo n, se estiver vazia retorna NULL

boolean expandExternal(abb *T, map_node *n);

boolean isExternal(map_node *n); // verifica se n um no externo

map_node *sibling(map_node *n); // retorna o no irmao de n

tipo_elem removeAboveExternal(abb *T, map_node *n); // remove um no externo

map_node *replaceElem(tipo_elem el, map_node *n); // substitui o elem de n por el e retorna n ou NULL

tipo_elem removeElem(abb *T, int id); // remove o no de chave k se existir

map_node *substitute(abb *T, map_node *n); // encontra um substituto para um no interno, para que se possa efetuar sua remocao

void printABB(abb *T, map_node *n); // percurso inter-fixado

void freeNodes(abb *T, map_node *n); // desalocar todos os nós da ABB
