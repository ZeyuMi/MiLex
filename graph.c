#include <stdlib.h>
#include "graph.h"

static struct vertex *graph = NULL;

int isVertexExist(int);
int isConnectTo(int, int);
struct vertex *getVertex(int);


int addVertex(int state, char *action){
	if(isVertexExist(state))
			return 0;
	struct vertex *v = malloc(sizeof(struct vertex));
	v->state = state;
	v->edges = NULL;
	v->action = action;
	v->next = NULL;

	if(NULL == graph){
		graph = v;
	}else{
		struct vertex *temp = graph;
		while(NULL != temp->next){
			temp = temp->next;
		}
		temp->next = v;
	}
	return 1;
}


int addEdge(int state1, int state2, char symbol){
	if(!isVertexExist(state1) || !isVertexExist(state2))
		return 0;
	if(isConnectTo(state1,state2))
		return 0;

	struct vertex *v1 = getVertex(state1);
	struct vertex *v2 = getVertex(state2);
	struct edge *newEdge = malloc(sizeof(struct edge));
	newEdge->connectsTo = v2;
	newEdge->symbol = symbol;
	newEdge->next = NULL;

	struct edge *edgetemp = v1->edges;
	if(NULL == edgetemp){
		v1->edges = newEdge;
	}else{
		while(NULL != edgetemp->next){
			edgetemp = edgetemp->next;
		}
		edgetemp->next = newEdge;
	}
	return 1;
}

void destroyVertex(struct vertex *v);
void destroyEdge(struct edge *e);

void destroy(){
	if(NULL != graph){
		destroyVertex(graph);
		graph = NULL;
	}
}


void destroyVertex(struct vertex *v){
	if(NULL != v->next){
		destroyVertex(v->next);
	}
	destroyEdge(v->edges);
	v->next = NULL;
	v->edges = NULL;
	free(v->action);
	free(v);
}

void destroyEdge(struct edge *e){
	if(NULL == e)
		return;
	if(NULL != e->next){
		destroyEdge(e->next);
	}
	e->connectsTo = NULL;
	e->next = NULL;
	free(e);
}


int isVertexExist(int state){
	struct vertex *temp = graph;
	while(NULL != temp){
		if(temp->state == state)
			return 1;
		temp = temp->next;
	}
	return 0;
}


int isConnectTo(int state1, int state2){
	if(!isVertexExist(state1) || !isVertexExist(state2))
		return 0;

	struct vertex *v1 = getVertex(state1);

	struct edge *edgetemp = v1->edges;
	while(NULL != edgetemp){
		if(edgetemp->connectsTo->state == state2)
			return 1;
		edgetemp = edgetemp->next;
	}
	return 0;
}

struct vertex *getVertex(int state){
	struct vertex *temp = graph;
	while(NULL != temp){
		if(temp->state == state)
			return temp;
		temp = temp->next;
	}
	return NULL;
}
