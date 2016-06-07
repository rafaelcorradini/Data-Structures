#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "graph.h"

typedef struct {
    int value;
    List *adjacency;
} Vertex;

typedef struct {
    Node *vertex;
    Node *edge;
} AdjVertex;

typedef struct {
    double value;
    Node *v1;
    Node *v2;
    Node *adj_v1;
    Node *adj_v2;
} Edge;

struct graph {
    List *vertices;
    List *edges;
};

typedef enum { FALSE, TRUE } boolean;

Graph *initGraph(void) {
    Graph *G;
    
    G = (Graph*) malloc(sizeof(Graph));
    G->vertices = initList();
    G->edges = initList();
    
    return G;
}

void freeGraph(Graph *G) {
    Node *v;
    
    freeList(G->edges, G->edges->head);
    for (v = G->vertices->head; v != NULL;) {
        freeList(((Vertex*) v->el)->adjacency, ((Vertex*) v->el)->adjacency->head);
        v = v->next;
    }
    freeList(G->vertices, G->vertices->head);
    free(G);
}

Node *opposite(Graph *G, Node *v, Node *e) {
    if (e == NULL || v == NULL)
        return NULL;
    if (((Edge*) e->el)->v1 == v)
        return ((Edge*) e->el)->v2;
    else
        return ((Edge*) e->el)->v1;
}

int areAdjacent(Graph *G, Node *v, Node *w) {
    Node *n;

    if (((Vertex*) v->el)->adjacency->count < ((Vertex*)w->el)->adjacency->count) {
        for(n = ((Vertex*) v->el)->adjacency->head; n != NULL;) {
            if(((AdjVertex*) n->el)->vertex == w)
                return TRUE;
            n = n->next;
        }
    } else {
        for(n = ((Vertex*)v->el)->adjacency->head; n != NULL;) {
            if(((AdjVertex*) n->el)->vertex == v)
                return TRUE;
            n = n->next;
        }
    }

    return FALSE;
}

void replaceVertex(Graph *G, Node *v, int o) {
    if (v != NULL)
        ((Vertex*) v->el)->value = o;
}

void replaceEdge(Graph *G, Node *e, double o) {
    if (e != NULL)
        ((Edge*) e->el)->value = o;
}

Node *insertVertex(Graph *G, int o) {
    Node *n;
    List *l;
    Vertex *elem;

    l = initList();
    n = insertList(G->vertices);
    n->el = (Vertex*) malloc(sizeof(Vertex));
    elem = ((Vertex*) n->el);
    elem->value = o;
    elem->adjacency = l;

    return n;
}

Node *insertEdge(Graph *G, Node *v, Node *w, double o)  {
    Node *n, *aux;
    Edge *elem;

    if (v == NULL || w == NULL)
        return NULL;

    n = insertList(G->edges);
    n->el = (Edge*) malloc(sizeof(Edge));
    elem = (Edge*) n->el;
    elem->value = o;
    elem->v1 = v;
    elem->v2 = w;

    aux = insertList(((Vertex*) w->el)->adjacency);
    aux->el = (AdjVertex*) malloc(sizeof(AdjVertex));
    ((AdjVertex*) aux->el)->edge = n;
    ((AdjVertex*) aux->el)->vertex = v;  

    elem->adj_v1 = aux;

    aux = insertList(((Vertex*) v->el)->adjacency);
    aux->el = (AdjVertex*) malloc(sizeof(AdjVertex));
    ((AdjVertex*) aux->el)->edge = n;
    ((AdjVertex*) aux->el)->vertex = w; 

    elem->adj_v2 = aux;

    return n;
}



// private function, used in removeVertex()
void removeIncidentEdges(Graph *G, Node *start) {
    if (start->next != NULL)
        removeIncidentEdges(G, start->next);

    removeEdge(G, ((AdjVertex*) start->el)->edge);
}

int removeVertex(Graph *G, Node *v) {
    Node *n;
    Vertex *aux;
    Vertex ret;

    if (v == NULL) {
        return -1;
    }

    if (((Vertex*) v->el)->adjacency->head != NULL)
        removeIncidentEdges(G, ((Vertex*) v->el)->adjacency->head);
    freeList(((Vertex*) v->el)->adjacency, ((Vertex*) v->el)->adjacency->head);

    aux = (Vertex*) removeList(G->vertices, v);
    ret = *aux;
    free(aux);
    return ret.value;
}

double removeEdge(Graph *G, Node *e) {
    Edge *aux;
    AdjVertex *aux2;
    Edge ret;

    aux = (Edge*) e->el;
    aux2 = (AdjVertex*) removeList(((Vertex*) aux->v1->el)->adjacency, aux->adj_v2);
    free(aux2);
    aux2 = (AdjVertex*) removeList(((Vertex*) aux->v2->el)->adjacency, aux->adj_v1);
    free(aux2);

    aux = (Edge*) removeList(G->edges, e);
    ret = *aux;
    free(aux);

    return ret.value;
}

int vertexValue(Graph *G, Node *v) {
    return ((Vertex*) v->el)->value;
}

double edgeValue(Graph *G, Node *e) {
    return ((Edge*) e->el)->value;
}

int numVertices(Graph *G) {
    return G->vertices->count; 
}

int numEdges(Graph *G) {
    return G->edges->count;
}

int degree(Graph *G, Node *v) {
    return ((Vertex*) v->el)->adjacency->count;
}
