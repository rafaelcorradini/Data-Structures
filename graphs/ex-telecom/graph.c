#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
    n->elem.dentro = FALSE;

    return n;
}

node *insertEdgeNode(graph* g, node* v, node *w, type_elem el)  {
    node *n;

    if (v == NULL || w == NULL) 
        return NULL;

    n = insert(g->edges, el);
    n->v1 = v;
    n->v2 = w;
    n->type = 'e';

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
    printf(" (%d - %d) %lf \n", start->v1->elem.id, start->v2->elem.id, start->elem.dist);
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


// funções ex telecomunicações
void makeGraphConnectivity(graph* g, node* v) {
    node* w;
    int i, id = 0;
    double d;
    type_elem el;

    
    while (v != NULL) {
        w = v->next;
        while (w != NULL) {
            d = (v->elem.longitude - w->elem.longitude) * (v->elem.longitude - w->elem.longitude);
            d = d + ((v->elem.latitude - w->elem.latitude) * (v->elem.latitude - w->elem.latitude));
            el.id = ++id;
            el.dist = sqrt(d);
            insertEdgeNode(g, v, w, el);
            w = w->next;
        }
        v = v->next;
    }  
}

void primJarnik(graph* g) {
    list *l;
    node *e, *v, *w, *z;
    type_elem el;

    l = initList();
    v = g->vertices->head;
    while (v != NULL) {
        if (v == g->vertices->head)
            v->elem.dist = 0;
        else 
            v->elem.dist = 9999999;

        insert(l, v->elem);
        v = v->next;
    }

    while (TRUE) {
        el = removeFromEndOrBegin(l, 'b');
        if (el.id == 0)
            break;
        w = searchId(g->vertices, g->vertices->head, el.id);
        w->elem.dentro = TRUE; 
        
        e = g->edges->head;
        while (e != NULL) {
            if (e->v1 == w || e->v2 == w) {
                z = opposite(g, w, e);
                if (z->elem.dentro == FALSE && z->elem.dist > e->elem.dist) {
                    z->elem.dist = e->elem.dist;
                    z->parent = w;
                    replacePriority(l, searchId(l, l->head, z->elem.id), z->elem);
                }
            }
            e = e->next;
        }
    }
    
    eraseList(l, l->head);
}

void printCities(graph* g) {
    node *v, *n, *x;
    list *l;

    l = initList();
    v = g->vertices->head;

    while (v != NULL) {
        insertPriorityId(l, v->elem);
        v = v->next;
    }

    v = l->head;   
    while (v != NULL) {
        n = searchId(g->vertices, g->vertices->head, v->elem.id);
        if (n->parent != NULL && n->parent != g->vertices->head) {
            if (n->parent->elem.id > n->elem.id)
                printf("%d %d\n", n->elem.id, n->parent->elem.id);
            else 
                printf("%d %d\n", n->parent->elem.id, n->elem.id);
        }
        v = v->next;
    }
    eraseList(l, l->head);   
}

double totalCities(graph* g) {
    node *v, *z;
    double total = 0;

    v = g->vertices->head;
    while (v != NULL) {
        if (v->parent != NULL) {
            total = total + v->elem.dist;
        }        
        v = v->next;
    }
    return total;
}