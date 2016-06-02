typedef struct {
	int id;
	char name[40];
} type_elem;

struct list_node {
	type_elem elem;
	struct list_node *next;
	struct list_node *prev;
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
int insert(list *l, type_elem el);

// insert in top of the list
int insertBegin(list *l, type_elem el);

// search by id (start: where starts the search)
node *searchId(list *l, node *start, int id);

// remove node
type_elem remove(list *l, node *n);

// remove by id
type_elem removeId(list *l, int id);

// remove from end or begin(flags: b - begin, e - end)
type_elem removeFromEndOrBegin(list *l, char flag);

// print all the nodes (start: where starts the search)
void printList(list *l, node *start, char orderby);