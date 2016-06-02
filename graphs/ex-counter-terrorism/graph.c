#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "graph.h"

graph* initGraph(void) {
    graph* g;
    
    g = (graph*) malloc(sizeof(graph));
    g->vertices = initList();
    g->edges = initList();
    
    return g;
}

void eraseGraph(graph* g) {
    eraseList(g->edges, g->edges->head);
    eraseList(g->vertices, g->vertices->head);
    free(g);
}

node *insertVertex(graph* g, type_elem el) {
    node *n;
    n = insert(g->vertices, el);
    n->type = 'v';

    return n;
}

node *insertEdge(graph* g, int v, int w, type_elem el)  {
    node *n;

    if (searchId(g->vertices, g->vertices->head, v) == NULL || searchId(g->vertices, g->vertices->head, w) == NULL) 
        return NULL;

    n = insert(g->edges, el);
    n->v1 = searchId(g->vertices, g->vertices->head, v);
    n->v2 = searchId(g->vertices, g->vertices->head, w);
    n->type = 'e';

    return n;
}

void replaceVertex(graph* g, int v, type_elem el) {
    node *n;

    n = searchId(g->vertices, g->vertices->head, v);
    n->elem = el;
}

void replaceEdge(graph* g, int e, type_elem el) {
    node *n;

    n = searchId(g->edges, g->edges->head, e);
    n->elem = el;
}

// private function, used in removeVertex()
void removeIncidentEdges(graph* g, node *n, node *start) {
    if (g->edges->head == NULL)
        return;

    if (start->next != NULL)
        removeIncidentEdges(g, n, start->next);

    if (start->v1 == n || start->v2 == n) 
        removeNode(g->edges, start);
}

type_elem removeVertex(graph* g, int v) {
    node *n;

    n = searchId(g->vertices, g->vertices->head, v);
    if (n != NULL) {
        removeIncidentEdges(g, n, g->edges->head);
    }
    return removeNode(g->vertices, n);
}

type_elem removeEdge(graph* g, int e) {
    return removeId(g->edges, e);
}

// private function
// int *AdjacencyListId(graph* g, node *v, node *start, int* r) {
//     int i = 0;

//     if (start->v1 == v) {
//         r[i++] = start->v2->elem.id;
//     } else if (start->v2 == v) {
//         r[i++] = start->v1->elem.id;
//     }
//     if (start->next != NULL) 
//         AdjacencyListId(g, v, start->next, r);
//     if (start->next == g->edges->head)
//         return r;
// }

int numVertices(graph* g) {
    
    return g->vertices->count;
    
}

int numEdges(graph* g) {
    return g->edges->count;
}

int degree(graph* g, node *v) {
    node *e;
    int i = 0;

    for (e = g->edges->head; e != NULL;) {
        if(e->v1 == v || e->v2 == v)
            i++;
        e = e->next;
    }
    return i;
}

int degreeId(graph *g, int v) {
    return degree(g, searchId(g->vertices, g->vertices->head, v));
}

// private function, used in areAdjacent()
boolean areAdjacentAux(graph* g, node* v, node* w, node* start) {
    int i = 0;

    i++;
    if (start->v1 == v && start->v2 == w || start->v1 == w && start->v2 == v )
        return TRUE;

    if (start->next != NULL) 
        areAdjacentAux(g, v, w, start->next);

    if (i >= g->edges->count)
        return 0;
}


boolean areAdjacent(graph* g, int v, int w) {
    return areAdjacentAux(g, searchId(g->vertices, g->vertices->head, v), searchId(g->vertices, g->vertices->head, w), g->edges->head);
}



void printVertices(graph* g) {
    printList(g->vertices, g->vertices->head, 'a');
}


// private function used in printEdges
void printEdgesAux(graph *g, node *start) {
    if (g->edges->count == 0) return;
    printf("%d ", start->elem.id);
    printf(" (%d - %d)\n", start->v1->elem.id, start->v2->elem.id);
    if(start->next != NULL) {
        printEdgesAux(g, start->next);
    }
}

void printEdges(graph* g) {
    printEdgesAux(g, g->edges->head);
}


void printGraph(graph* g) {
    printVertices(g);
    printEdges(g);
}

void bubbleSort(node** v, int n) {
   int i, j;
   node* aux;

   for( i = 0; i < ( n -1 );  i++ ) {
      for( j=0; j <( n -( i +1 ) ); j++ ) {
         if( v[j]->elem.coreness > v[j+1]->elem.coreness )   {          
            aux = v[j];
            v[j] = v[j+1];
            v[j+1] = aux;
         }
      } 
   }
}

void kcore(graph* g) {
    node *v, *e, *u, **arr;
    int i = 0;

    arr = (node **) malloc( g->vertices->count * sizeof(node*));
    for (v = g->vertices->head; v != NULL;) {
        v->elem.coreness = degree(g, v);
        arr[i] = v;
        i++;

        v = v->next;
    }

    bubbleSort(arr, g->vertices->count);

    for (i = 0; i < g->vertices->count; i++) {
        for (e = g->edges->head; e != NULL;) {
            if (e->v1 == arr[i] || e->v2 == arr[i])  {
                if(e->v1 == arr[i]) u = e->v2;
                else u = e->v1;

                if(u->elem.coreness > arr[i]->elem.coreness) {
                    u->elem.coreness--;
                    bubbleSort(arr, g->vertices->count);
                }

            }
            e = e->next;
        }
    }
}



