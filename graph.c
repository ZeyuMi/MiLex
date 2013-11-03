#include <stdlib.h>
#include "graph.h"

static struct vertex *graph = NULL;

int addVertex(int state, char *action){
	struct vertex *v = malloc(sizeof(struct vertex));
	v->state = state;
	v->edges = NULL;
	v->action = action;
	v->next = NULL;

	if(NULL == result){
		result = v;
	}else{
		struct vertex *temp = result;
		if(state == temp->state)
			return 0;
		while(NULL != temp->next){
			if(state == temp->next->state)
				return 0;
			temp = temp->next;
		}
		temp->next = v;
	}
	return 1;
}

int isVertexExist(int);
int isConnectTo(int, int);
struct vertex *getVertex(int);


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

	while(NULL != v1->edges){
		v1 = v1->edges->connectsTo;
	}
	v1->edges = newEdge;
	return 1;
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

	struct edge *e = v1->edges;
	while(NULL != e){
		if(e->connectsTo->state = state2)
			return 1;
		e = e->connectsTo->edges;
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
