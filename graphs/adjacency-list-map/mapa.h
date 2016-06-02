#include "abb.h"

abb *define(); //inicializa o mapa
tipo_elem search(char k[30], abb *M); //retorna o elemento com chave k do mapa M, caso exista. Caso contrário, retorna elemento nulo.
boolean insert(tipo_elem x, abb *M); //insere o elemento x no mapa M e retorna true, caso não exista elemento em M com a mesma chave de x. Se já existir elemento em M com a mesma chave de x, retorna false.
boolean replace(tipo_elem x, abb *M); //Substitui por x o elemento do mapa M com a mesma chave de x, se tal elemento existe em M, retornando true. Caso contrário retorna false. 
tipo_elem remover(char k[30], abb *M); //remove e retorna o elemento com chave k, caso este exista no mapa M. Caso contrário retorna elemento nulo.
void print(abb *M);
void freeNodesMap(abb *M, node *n);