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

node* opposite(graph* g, node* v, node* e) {
    if (e->v1 != v && e->v2 != v)
        return NULL;

    if (e->v1 == v)
        return e->v2;
    else
        return e->v1;
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

// private function, used in degree()
int degreeAux(graph* g, node *v, node *start) {
    int i = 0;

    if (start->v1 == v) {
        i++;
    } else if (start->v2 == v) {
        i++;
    }
    if (start->next != NULL) 
        degreeAux(g, v, start->next);
    if (start->next == g->edges->head)
        return i;
}

int degree(graph *g, int v) {
    return degreeAux(g, searchId(g->vertices, g->vertices->head, v), g->edges->head);
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
    printf(" (%d - %d) value: %lf\n", start->v1->elem.id, start->v2->elem.id, start->elem.value);
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

boolean bellmanford(graph* g, node* start) {
    int i;
    boolean flag;
    node *v, *e, *z;
    for (v = g->vertices->head; v != NULL;) {
        if(v == start) {
            v->elem.dist = 0;
            v->parent = NULL;
        }
        else
            v->elem.dist = 9999999;
        v = v->next;
    }
    for (i = 0; i < g->vertices->count; i++) {
        flag = TRUE;
        for (v = g->vertices->head; v != NULL;) {
            for (e = g->edges->head; e != NULL;) {
                if(e->v1 == v || e->v2 == v) {
                    z = opposite(g, v, e);
                    if((z->elem.dist + e->elem.value) < v->elem.dist) {
                        v->elem.dist = z->elem.dist + e->elem.value;
                        v->parent = z;
                        flag = FALSE;
                    }
                }
                e = e->next;
            }
            v = v->next;
        }
        if(flag == TRUE)
            return TRUE;
    }
    return FALSE;
} 

void setConsultor(graph* g, node* v) {
    if(v != NULL)
        v->elem.c = TRUE;
}