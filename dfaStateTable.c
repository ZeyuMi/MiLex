#include <stdlib.h>
#include "lex.h"
#include "dfaStateTable.h"

typedef struct dfaStateTableEntry{
	int state;
	int *nfaStates;
	int marked;
	struct dfaStateTableEntry *next;
} entry;

static int stateNum = 0;
static entry *table = NULL;
int compareTwoIntArray(int *, int*);
int *copyIntArray(int *);
int getIntArraySize(int *);

int installState(int *nfaStates){
	entry *temp = table;
	entry *pre = NULL;
	while(NULL != temp){
		if(compareTwoIntArray(temp->nfaStates, nfaStates)){
			return temp->state;
		}
		pre = temp;
		temp = temp->next;
	}
	entry *newEntry = malloc(sizeof(entry));
	newEntry->state = ++stateNum;
	newEntry->nfaStates = copyIntArray(nfaStates);
	newEntry->marked = 0;
	newEntry->next = NULL;
	pre->next = newEntry;
	return stateNum;
}


int unmarkedStatesExist(){
	int state = getUnmarkedState();
	if(state > 0)
		return 1;
	else
		return 0;
}


int getUnmarkedState(){
	entry *temp = table;
	while(NULL != temp){
		if(0 == temp->marked)
			return temp->state;
		temp = temp->next;
	}
	return 0;
}


void markState(int state){
	entry *temp = table;
	while(NULL != temp){
		if(state == temp->state){
			temp->marked = 1;
			return;
		}
		temp = temp->next;
	}
}


int *getNFAStates(int state){
	entry *temp = table;
	while(NULL != temp){
		if(state == temp->state)
			return temp->nfaStates;
		temp = temp->next;
	}
	return NULL;
}


void destroyDFATable(){
	entry *temp = table;
	entry *next = NULL;
	while(NULL != temp){
		next = temp->next;
		temp->state = 0;
		free(temp->nfaStates);
		temp->nfaStates = NULL;
		temp->marked = 0;
		temp->next = NULL;
		free(temp);
		temp = next;
	}
	table = NULL;
}


int compareTwoIntArray(int *A, int *B){
	int sizeA = getIntArraySize(A);
	int sizeB = getIntArraySize(B);
	if(sizeA != sizeB)
		return 0;
	int i = -1;
	while(1){
		i++;
		if(*(A+i) != *(B+i))
			return 0;
		if(-1 == *(A+i))
			return 1;
	}
}


int *copyIntArray(int *array){
	int size = getIntArraySize(array);
	int *newArray = malloc(sizeof(int) * size);
	int i = 0;
	while(-1 != (*(newArray+i) = *(array+i)))
		i++;
	return newArray;
}


int getIntArraySize(int *array){
	int size = 0;
	while(-1 != *(array+(size++)))
		;
	return size;
}
