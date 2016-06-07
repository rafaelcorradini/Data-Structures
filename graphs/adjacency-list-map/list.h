struct list_node {
	void *el; // element(vertex or edge)
	struct list_node *next;
	struct list_node *prev;
};
typedef struct list_node Node;

typedef struct {
	int count;
	Node *head, *tail;
} List;


// inicializa a lista
List *initList();

// desaloca os elementos da lista e a lista
void freeList(List *L, Node *n);

// insere um elemento na lista
Node *insertList(List *L);

// remove um elemento da lista
void *removeList(List *L, Node *n);