#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"

#define DEFAULT 100 

typedef struct intBufferEntry{
	int id;
	int *buffer;
	int *bufp;
	int buffersize;
	struct intBufferEntry *next;
} intEntry;

typedef struct charBufferEntry{
	int id;
	char *buffer;
	int *bufp;
	char buffersize;
	struct charBufferEntry *next;
} charEntry;


static charEntry *charBufferList = NULL;
static intEntry *intBufferList = NULL;
int charNum = 0;
int intNum = 0;

void memError();
charEntry *findCharEntry(int);
intEntry *findIntEntry(int);

int initializeCharBuffer(){
	charEntry *temp = charBufferList;
	charEntry *pre = NULL;
	while(NULL != temp){
		pre = temp;
		temp = temp->next;
	}
	temp = malloc(sizeof(charEntry));
	if(NULL == temp)
		memError();
	temp->id = ++charNum;
	temp->buffersize = DEFAULT;
	temp->bufp = temp->buffer = malloc(DEFAULT);
	if(NULL == temp->bufp)
		memError();
	temp->next = NULL;
	if(NULL == table)
		table = temp;
	else
		pre->next = temp;
	return charNum;
}

void initializeIntBuffer(){
	intEntry *temp = intBufferList;
	intEntry *pre = NULL;
	while(NULL != temp){
		pre = temp;
		temp = temp->next;
	}
	temp = malloc(sizeof(intEntry));
	if(NULL == temp)
		memError();
	temp->id = ++intNum;
	temp->buffersize = DEFAULT;
	temp->bufp = temp->buffer = malloc(sizeof(int) * DEFAULT);
	if(NULL == temp->bufp)
		memError();
	temp->next = NULL;
	if(NULL == table)
		table = temp;
	else
		pre->next = temp;
	return intNum;
}


char *getCharBuffer(int id){
	charEntry *temp = charBufferList;
	while(NULL != temp){
		if(temp->id == id)
			return temp->buffer;
		temp = temp->next;
	}
	return NULL;
}


charEntry *findCharEntry(int id){
	charEntry *temp = charBufferList;
	while(NULL != temp){
		if(temp->id == id)
			return temp;
		temp = temp->next;
	}
	return NULL;
}


intEntry *findIntEntry(int id){
	intEntry *temp = intBufferList;
	while(NULL != temp){
		if(temp->id == id)
			return temp;
		temp = temp->next;
	}
	return NULL;
}


void addCharElement(int id, char c){
	charEntry *temp = findCharEntry(id); 
	if(NULL == temp)
		return;

	if(temp->bufp - temp->buffer >= temp->buffersize){
		temp->buffersize *= 2;
		char *old = temp->buffer;
		temp->buffer = malloc(temp->buffersize);
		if(temp->buffer == NULL)
			memError();
		memcpy((void *)temp->buffer, (void *)old, (temp->buffersize)/2);
		free(old);
		temp->bufp = temp->buffer + ((temp->buffersize)/2);
	}
	*((temp->bufp)++) = c;
}


void addIntElement(int id, int i){
	intEntry *temp = findIntEntry(id);
	if(NULL == temp)
		return;

	if(temp->bufp - temp->buffer >= temp->buffersize){
		temp->buffersize *= 2;
		char *old = temp->buffer;
		temp->buffer = malloc(sizeof(int) * temp->buffersize);
		if(temp->buffer == NULL)
			memError();
		memcpy((void *)temp->buffer, (void *)old, sizeof(int) * (temp->buffersize)/2);
		free(old);
		temp->bufp = temp->buffer + ((temp->buffersize)/2);
	}
	*((temp->bufp)++) = i;
}


void addCharElements(int id, char *s){
	while('\0' != *s){
		addCharElement(id, *s);
		s++;
	}
}


void removeCharLast(int id){
	charEntry *temp = findCharEntry(id);
	if(NULL == temp)
		return;
	if(temp->bufp == temp->buffer)
		return;
	else
		(temp->bufp)--;
}


void removeIntLast(){
	intEntry *temp = findIntEntry(id);
	if(NULL == temp)
		return;
	if(temp->bufp == temp->buffer)
		return;
	else
		(temp->bufp)--;
}


void destroyCharBuffer(){
	charBuffersize = 0;
	free(charBuffer);
	charBuffer = charBufp = NULL;
}


void destroyIntBuffer(){
	intBuffersize = 0;
	free(intBuffer);
	intBuffer = intBufp = NULL;
}


void rewindCharPointer(){
	charBufp = charBuffer;
}


void rewindIntPointer(){
	intBufp = intBuffer;
}


int charSize(){
	return charBufp - charBuffer;
}


int intSize(){
	return intBufp - intBuffer;
}


void fillIntArrayWithBuffer(int *array){
	int size = intSize();
	int i = 0;
	while(i < size){
		*(array+i) = *(intBuffer+i);
		i++;
	}
}


int isInIntBuffer(int i){
	int *temp = intBuffer;
	while(temp != intBufp){
		if(*temp == i)
			return 1;
		temp++;
	}
	return 0;
}


void memError(){
	fprintf(stderr, "memory error!\n");
	exit(EXIT_FAILURE);
}
