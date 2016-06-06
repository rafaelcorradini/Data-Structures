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

List *initList();

void freeList(List *L, Node *n);

Node *insertList(List *L);

void *removeList(List *L, Node *n);

// void printList(List *l, Node *start, char orderby);