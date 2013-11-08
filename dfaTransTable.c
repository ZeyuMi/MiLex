#include <stdlib.h>
#include <stdio.h>
#include "dfaTransTable.h"

typedef struct dfaTTEntry{
	int state;
	int *trans;
	struct dfaTTEntry *next;
}ttEntry;


static ttEntry *table;

void addDFATransTableEntry(int from, int to, char symbol){
	ttEntry *temp = table;
	ttEntry *pre = NULL;
	while(NULL != temp){
		if(temp->state == from){
			(temp->trans)[symbol] = to;
			return;
		}
		pre = temp;
		temp = temp->next;
	}
	temp = malloc(sizeof(ttEntry));
	temp->state = from;
	temp->trans = malloc(sizeof(int) * 128);
	int i = 0;
	while(i < 128)
		(temp->trans)[i] = 0;
	temp->next = NULL;
	pre->next = temp;
	*(temp->trans + symbol) = to;
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
		temp = temp->next;
	}
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
