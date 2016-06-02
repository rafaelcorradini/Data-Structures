#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main() {
	list *l;
	int i, id;
	type_elem el;
	l = initList();

	while(1) {
		printf("1 - Inserir no final\n");
		printf("2 - Inserir no começo\n");
		printf("3 - Remover do final\n");
		printf("4 - Remover do começo\n");
		printf("5 - Remover pelo id\n");
		printf("6 - Printar todos os nós\n");
		scanf(" %d", &i);
		id = 0;
		switch(i) {
			case 1: printf("\nid: ");
					scanf(" %d", &id);
					el.id = id;
					insert(l, el);
					break;

			case 2: printf("\nid: ");
					scanf(" %d", &id);
					el.id = id;
					insertBegin(l, el);
					break;

			case 3: removeFromEndOrBegin(l, 'e');
					break;

			case 4: removeFromEndOrBegin(l, 'b');
					break;

			case 5: printf("\nid: ");
					scanf(" %d", &id);
					removeId(l, id);
					break;

			case 6: printf("-------\n");
					printList(l, l->head, 'a');
					printf("-------\n");
					break;

			default: exit(1);

		}
	}
	return 0;

}