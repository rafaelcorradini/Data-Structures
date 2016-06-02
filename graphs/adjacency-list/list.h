typedef struct list List;

List *initList();

void eraseList(List *l, Node *n);

Node *insert(List *l, double value);

double remove(List *l, Node *n);

void printList(List *l, Node *start, char orderby);