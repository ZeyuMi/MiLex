#include <stdlib.h>
#include <stdio.h>
#include "dfaTransTable.h"

typedef struct dfaTTEntry{
	int state;
	int *trans;
	char *action;
	struct dfaTTEntry *next;
}ttEntry;


static ttEntry *table = NULL;

ttEntry *getEntry(int);

void addDFANewState(int state, char *action){
	ttEntry *temp = getEntry(state);
	if(NULL != temp)
		return;
	temp = table;
	ttEntry *pre = NULL;
	while(NULL != temp){
		pre = temp;
		temp = temp->next;
	}
	temp = malloc(sizeof(ttEntry));
	temp->state = state;
	temp->trans = malloc(sizeof(int) * 128);
	temp->action = action;
	int i = 0;
	while(i < 128){
		(temp->trans)[i] = 0;
		i++;
	}
	temp->next = NULL;
	if(NULL == table)
		table = temp;
	else
		pre->next = temp;
}


void addDFATransTableEntry(int from, int to, char symbol){
	ttEntry *temp = getEntry(from);
	if(NULL == temp)
		return;
	(temp->trans)[symbol] = to;
}


ttEntry *getEntry(int state){
	ttEntry *temp = table;
	while(NULL != temp){
		if(temp->state == state){
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}


void printDFATransTable(){
	ttEntry *temp = table;
	while(NULL != temp){
		printf("state%d: ", temp->state);
		int i = 0;
		while(i < 128){
			if(0 != (temp->trans)[i])
				printf("connects to state%d by %c,", (temp->trans)[i], i);
			i++;
		}
		if(NULL != temp->action)
			printf("action is %s", temp->action);
		printf("\n");
		temp = temp->next;
	}
	printf("\n");
}


void destroyDFATransTable(){
	ttEntry *temp = table;
	ttEntry *next = NULL;
	while(NULL != temp){
		next = temp->next;
		temp->state = 0;
		free(temp->trans);
		temp->trans = NULL;
		temp->next = NULL;
		free(temp);
		temp = next;
	}
	table = NULL;
}
