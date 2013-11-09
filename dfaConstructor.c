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
	int *nfaClosure = epsilonClosure(firstNFAState);
	int dfaState = installState(nfaClosure);
	char *action = getAction(nfaClosure);
	addDFANewState(dfaState, action);
	while(unmarkedStatesExist()){
		int state = getUnmarkedState();
		markState(state);
		int *nfaStates = getNFAStates(state);
		int i = 0;
		while(i < 128){
			int *reach = move(nfaStates, i);
			int *closure = epsilonClosure(reach);
			if(-1 == closure[0]){
				i++;
				continue;
			}
			dfaState = installState(closure);
			char *action = getAction(closure);
			addDFANewState(dfaState, action);
			addDFATransTableEntry(state, dfaState, i);
			i++;
		}
	}
}


void destroyDFA(){
	destroyDFATransTable();
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
	int bufferid = initializeIntBuffer();
	while(-1 != (temp = *(stateSet++))){
		addIntElement(bufferid, temp);
		pushStack(temp);
	}
	while(EMPTY != (temp = popStack())){
		int *reach = reachByEdgeSymbol(temp, EPSILON);
		int tempState = -1;
		while(-1 != (tempState = *(reach++))){
			if(!isInIntBuffer(bufferid, tempState)){
				addIntElement(bufferid, tempState);
				pushStack(tempState);
			}
		}
	}
	addIntElement(bufferid, -1);
	int *result = malloc(intSize(bufferid) * sizeof(int));
	fillIntArrayWithBuffer(bufferid, result);
	destroyIntBuffer(bufferid);
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
