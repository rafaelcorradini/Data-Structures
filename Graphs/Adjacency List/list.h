typedef struct {
	int id;
	char name[40];
} type_elem;

typedef enum { FALSE, TRUE } boolean;

struct list_node {
	type_elem elem;
	char type; // v - vertex, e -edge
	struct list_node *next;
	struct list_node *prev;
	struct list_node *v1;
	struct list_node *v2;
};
typedef struct list_node node;

typedef struct {
	int count;
	node *head, *tail;
} list;

// defines the list
list *initList();

// erase all the node and erase the list
void eraseList(list *l, node *n);

// insert in list order
node *insert(list *l, type_elem el);

// insert in top of the list
node *insertBegin(list *l, type_elem el);

// search by id (start: where starts the search)
node *searchId(list *l, node *start, int id);

// remove node, returns a empty element when fail
type_elem removeNode(list *l, node *n);

// remove by id, returns a empty element when fail
type_elem removeId(list *l, int id);

// remove from end or begin(flags: b - begin, e - end), returns a empty element when fail
type_elem removeFromEndOrBegin(list *l, char flag);

// print all the nodes (start: where starts the search)
void printList(list *l, node *start, char orderby);