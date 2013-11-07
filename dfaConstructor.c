#include <stdlib.h>
#include "lex.h"
#include "dfaConstructor.h"
#include "graph.h"

int *move(int *, char);
int *epsilonClosure(int *);
int *mergeIntArrays(int *, int *);

void constructDFA(){

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


int *epsilonClosure(int *stateSet){
	
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
	int result = malloc(sizeof(int) * size);
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
