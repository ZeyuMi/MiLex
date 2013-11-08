#include <stdlib.h>
#include "lex.h"
#include "dfaConstructor.h"
#include "graph.h"
#include "stack.h"
#include "buffer.h"
#include "dfaStateTable.h"
#include "dfaTransTable.h"

int *move(int *, char);
int *epsilonClosure(int *);
int *mergeIntArrays(int *, int *);

void constructDFA(){
	struct vertex *graph = getGraph();
	int startPoint = graph->state;
	int firstNFAState[2] = {startPoint, -1};
	installState(firstNFAState);
	while(unmarkedStatesExist()){
		int state = getUnmarkedState();
		markState(state);
		int *nfaStates = getNFAStates(state);
		char c = -1;
		int i = 0;
		while('\0' != (c = charset[i++])){
			int *reach = move(nfaStates, c);
			int *closure = epsilonClosure(reach);
			int dfaState = installState(closure);
			addDFATransTableEntry(state, dfaState, c);
		}
	}
	destroyDFATable();
}

int *move(int *stateSet, char c){
	int state = -1;
	int index = -1;
	int *result = malloc(sizeof(int));
	*(result) = -1;
	while(1){
		index++;
		state = *(stateSet+index);
		if(-1 == state){
			break;
		}
		int *reach = reachByEdgeSymbol(state, c);
		int *old = result;
		result = mergeIntArrays(result, reach);
		free(reach);
		free(old);
	}
	return result;
}

/*
	the returned pointer points to a allocated memory
*/
int *epsilonClosure(int *stateSet){
	clearStack();
	int temp = -1;
	initializeIntBuffer();
	while(-1 != (temp = *(stateSet++))){
		addIntElement(temp);
		push(temp);
	}
	while(EMPTY != (temp = pop())){
		int *reach = reachByEdgeSymbol(temp, EPSILON);
		int tempState = -1;
		while(-1 != (tempState = *(reach++))){
			if(!isInIntBuffer(tempState)){
				addIntElement(tempState);
				push(tempState);
			}
		}
	}
	addIntElement(-1);
	int *result = malloc(intSize() * sizeof(int));
	fillIntArrayWithBuffer(result);
	destroyIntBuffer();
	return result;
}


int *mergeIntArrays(int *arrayA, int *arrayB){
	int sizeA = 0;
	int sizeB = 0;
	int temp = 0;
	while(-1 != *(arrayA+(sizeA++)))
		;
	while(-1 != *(arrayB+(sizeB++)))
		;
	int size = sizeA + sizeB - 1;
	int* result = malloc(sizeof(int) * size);
	int i = 0;
	int j = 0;
	while(i < sizeA-1){
		*(result+j) = *(arrayA+i);
		i++;
		j++;
	}
	i = 0;
	while(i < sizeB-1){
		*(result+j) = *(arrayB+i);
		i++;
		j++;
	}
	*(result+j) = -1;
	return result;
}
