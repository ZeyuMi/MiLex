#include <stdlib.h>
#include <stdio.h>
#include "graph.h"
#include "buffer.h"

static struct vertex *graph = NULL;


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

void destroyGraph(){
	if(NULL != graph){
		destroyVertex(graph);
		graph = NULL;
	}
}

/*
	the returned pointer points to a allocated memory
*/
int *reachByEdgeSymbol(int state, char symbol){
	if(!isVertexExist(state))
		return NULL;
	int bufferid = initializeIntBuffer();
	struct vertex *vertexTemp = getVertex(state);
	struct edge *edgeTemp = vertexTemp->edges;
	while(NULL != edgeTemp){
		if(symbol == edgeTemp->symbol)
			addIntElement(bufferid, edgeTemp->connectsTo->state);
		edgeTemp = edgeTemp->next;
	}
	addIntElement(bufferid, -1);
	int *result = malloc(intSize(bufferid) * sizeof(int));
	fillIntArrayWithBuffer(bufferid, result);
	destroyIntBuffer(bufferid);
	return result;
}


int addActionToVertex(int state, char *action){
	if(!isVertexExist(state))
		return 0;
	struct vertex *temp = getVertex(state);
	temp->action = action;
	return 1;
}


char *getAction(int *states){
	int temp = 0;
	while(-1 != (temp = *states)){
		struct vertex *vertexTemp = getVertex(temp);
		if(NULL != vertexTemp && NULL != vertexTemp->action)
			return vertexTemp->action;
		states++;
	}
	return NULL;
}


void printGraph(){
	struct vertex *vertexTemp = graph;
	while(NULL != vertexTemp){
		printf("vertex%d connects to ", vertexTemp->state);
		struct edge *edgeTemp = vertexTemp->edges;
		while(NULL != edgeTemp){
			printf("vertex%d labeled %c, ", edgeTemp->connectsTo->state, edgeTemp->symbol);
			edgeTemp = edgeTemp->next;
		}
		if(NULL != vertexTemp->action)
			printf("action is %s.", vertexTemp->action);
		printf("\n");
		vertexTemp = vertexTemp->next;
	}
	printf("\n");
}


void destroyVertex(struct vertex *v){
	if(NULL != v->next){
		destroyVertex(v->next);
	}
	destroyEdge(v->edges);
	v->next = NULL;
	v->edges = NULL;
	v->action = NULL;
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


struct vertex *getGraph(){
	return graph;
}
