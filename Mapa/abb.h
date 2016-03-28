typedef struct {
	char chave[30];
	char info[30];
} tipo_elem;

struct abb_node {
	tipo_elem elem;
	struct abb_node *leftChild, *rightChild, *parent;
};
typedef struct abb_node node;

typedef struct {
	int nelem;
	node *root;
} abb;

typedef enum { FALSE, TRUE } boolean;

abb *defineABB(); // inicializa a arvore e retorna ela mesma

boolean isEmpty(abb *T); // retorna 1 se arvore estiver vazia e 0 se nao estiver

node *insertElem(abb *T, tipo_elem el); // insere um elemento na arvore retorna o nodo no qual foi inserido, NULL se falhar

node *searchElem(abb *T, char k[30], node *n); // inicia uma pesqusia a partir do nodo n, se estiver vazia retorna NULL

boolean expandExternal(abb *T, node *n);

boolean isExternal(node *n); // verifica se n um no externo

node *sibling(node *n); // retorna o no irmao de n

tipo_elem removeAboveExternal(abb *T, node *n); // remove um no externo

node *replaceElem(tipo_elem el, node *n); // substitui o elem de n por el e retorna n ou NULL

tipo_elem removeElem(abb *T, char k[30]); // remove o no de chave k se existir

node *substitute(abb *T, node *n); // encontra um substituto para um no interno, para que se possa efetuar sua remocao

void printABB(abb *T, node *n); // percurso inter-fixado

void freeNodes(abb *T, node *n); // desalocar todos os nós da ABB
