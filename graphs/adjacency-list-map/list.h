struct list_node {
	void* el; // element(vertex or edge)
	struct list_node next;
	struct list_node prev;
};
typedef struct list_node Node;

typedef struct list List;

List *initList();

void eraseList(List *l, Node *n);

Node *insert(List *l, double value);

double remove(List *l, Node *n);

void printList(List *l, Node *start, char orderby);