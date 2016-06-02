#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "graph.h"

typedef struct {
    int value;
    List *adjacency;
} Vertex;

typedef struct {
    Node* vertex;
    Node* edge;
} AdjVertex;

typedef struct {
    double value;
    Node* v1;
    Node* v2;
    Node* adj_v1;
    Node* adj_v2;
} Edge;

typedef struct {
    List *vertices;
    List *edges;
} graph;

graph* initGraph(void) {
    graph* G;
    
    G = (graph*) malloc(sizeof(graph));
    G->vertices = initList();
    G->edges = initList();
    
    return G;
}

void eraseGraph(graph* G) {
    eraseList(G->edges, G->edges->head);
    eraseList(G->vertices, G->vertices->head);
    free(G);
}

Node *opposite(graph* G, Node* v, Node* e) {
    if (e == NULL || v == NULL)
        return NULL;
    if (e->el->v1 == v)
        return e->el->v2;
    else
        return e->el->v1;
}

int areAdjacent(graph* G, Node* v, Node* w) {
    Node* n;

    if (v->adjacency->count < w->adjacency->count) {
        for(n = v->adjacency->head; n != NULL; n != NULL ? n->next) {
            if(n->vertex == w)
                return TRUE;
        }
    } else {
        for(n = w->adjacency->head; n != NULL; n != NULL ? n->next) {
            if(n->vertex == v-)
                return TRUE;
        }
    }

    return FALSE;
}

void replaceVertex(graph* G, Node* v, int o) {
    if (v != NULL)
        v->el->value = o;
}

void replaceEdge(graph* G, Node* e, double o) {
    if (e != NULL)
        e->el->value = o;
}

Node *insertVertex(graph* G, int o) {
    Node* n;
    list* l;

    l = (list*) malloc(sizeof(list));
    n = insert(G->vertices);
    n->el = (Vertex*) malloc(sizeof(Vertex));
    n->el->value = o;
    n->el->adjacency = l;
    G->vertices->count++;

    return n;
}

Node *insertEdge(graph* G, Node* v, Node* w, double o)  {
    Node *n, aux;

    if (v == NULL || w == NULL)
        return NULL;

    n = insert(G->edges);
    n->el = (Edge*) malloc(sizeof(Edge));
    n->el->value = o;
    n->el->v1 = v;
    n->el->v2 = w;
    aux = insert(v->el->adjacency);
    aux->el = (AdjVertex*) malloc(sizeof(AdjVertex));
    aux->el->edge = n;
    aux->el->vertex = w;  
    n->el->adj_v1 = aux;
    aux = insert(w->el->adjacency);
    aux->el = (AdjVertex*) malloc(sizeof(AdjVertex));
    aux->el->edge = n;
    aux->el->vertex = v; 
    n->el->adj_v2 = aux;
    G->edges->count++;

    return n;
}



// private function, used in removeVertex()
void removeIncidentEdges(graph* G, Node *n, Node *start) {

    if (start->next != NULL)
        removeIncidentEdges(g, n, start->next);

    remove(G->edges, start->el->edge);
}

int removeVertex(graph* G, Node* v) {
    Node* n;

    if (v == NULL) {
        return -1;
    }

    if (v->el->adjacency->head != NULL)
        removeIncidentEdges(G, v, v->el->adjacency->head);
    eraseList(v->el->adjacency, v->el->adjacency->head);
    G->vertices->count--;

    return (int) remove(G->vertices, v);
}

double removeEdge(graph* G, Node* e) {
    remove(e->el->adj_v1->vertex->el->adjacency, e->el->adj_v1);
    remove(e->el->adj_v2->vertex->el->adjacency, e->el->adj_v2);
    G->edges->count--;

    return remove(G->edges, e);
}

int vertexValue(Graph* G, node* v) {
    return v->el->value;
}

double edgeValue(Graph* G, node* e) {
    return e->el->value;
}

int numVertices(graph* G) {
    return G->vertices->count; 
}

int numEdges(graph* G) {
    return G->edges->count;
}

int degree(graph *g, Node* v) {
    return v->adjacency->count;
}


//// acaba aqui

void printVertices(graph* G) {
    printList(G->vertices, G->vertices->head, 'a');
}


// private function used in printEdges
// void printEdgesAux(graph *g, Node *start) {
//     if (G->edges->count == 0) return;
//     printf("%d ", start->el);

//     if (start->next != NULL) {
//         printEdgesAux(g, start->next);
//     }
// }

// void printEdges(graph* G) {
//     printEdgesAux(g, G->edges->head);
// }


// void printGraph(graph* G) {
//     printVertices(g);
//     printEdges(g);
// }