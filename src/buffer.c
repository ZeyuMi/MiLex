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
	char *bufp;
	int buffersize;
	struct charBufferEntry *next;
} charEntry;


static charEntry *charBufferList = NULL;
static intEntry *intBufferList = NULL;
int charNum = 0;
int intNum = 0;

void memError();
charEntry *findCharEntry(int);
intEntry *findIntEntry(int);
charEntry *findPreCharEntry(int);
intEntry *findPreIntEntry(int);

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
	if(NULL == charBufferList)
		charBufferList = temp;
	else
		pre->next = temp;
	return charNum;
}

int initializeIntBuffer(){
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
	if(NULL == intBufferList)
		intBufferList = temp;
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


charEntry *findPreCharEntry(int id){
	charEntry *temp = charBufferList;
	while(NULL != temp && NULL != temp->next){
		if(temp->next->id == id)
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


intEntry *findPreIntEntry(int id){
	intEntry *temp = intBufferList;
	while(NULL != temp && NULL != temp->next){
		if(temp->next->id == id)
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
		int *old = temp->buffer;
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


void removeIntLast(int id){
	intEntry *temp = findIntEntry(id);
	if(NULL == temp)
		return;
	if(temp->bufp == temp->buffer)
		return;
	else
		(temp->bufp)--;
}


void destroyCharBuffer(int id){
	charEntry *temp = NULL;
	if(charBufferList->id == id){
		temp = charBufferList;
		charBufferList = charBufferList->next;
	}else{
		charEntry *pre = findPreCharEntry(id);
		if(NULL == pre)
			return;
		temp = pre->next;
		pre->next = pre->next->next;
	}
	temp->id = 0;
	temp->buffersize = 0;
	free(temp->buffer);
	temp->bufp = temp->buffer = 0;
	temp->next = NULL;
}


void destroyIntBuffer(int id){
	intEntry *temp = NULL;
	if(intBufferList->id == id){
		temp = intBufferList;
		intBufferList = intBufferList->next;
	}else{
		intEntry *pre = findPreIntEntry(id);
		if(NULL == pre)
			return;
		temp = pre->next;
		pre->next = pre->next->next;
	}
	temp->id = 0;
	temp->buffersize = 0;
	free(temp->buffer);
	temp->bufp = temp->buffer = 0;
	temp->next = NULL;
}


void rewindCharPointer(int id){
	charEntry *temp = findCharEntry(id);
	if(NULL == temp)
		return;
	temp->bufp = temp->buffer;
}


void rewindIntPointer(int id){
	intEntry *temp = findIntEntry(id);
	if(NULL == temp)
		return;
	temp->bufp = temp->buffer;
}


int charSize(int id){
	charEntry *temp = findCharEntry(id);
	if(NULL == temp)
		return 0;
	return temp->bufp - temp->buffer;
}


int intSize(int id){
	intEntry *temp = findIntEntry(id);
	if(NULL == temp)
		return 0;
	return temp->bufp - temp->buffer;
}


void fillIntArrayWithBuffer(int id, int *array){
	intEntry *temp = findIntEntry(id);
	if(NULL == temp)
		return;
	int size = intSize(id);
	int i = 0;
	while(i < size){
		*(array+i) = *((temp->buffer)+i);
		i++;
	}
}


int isInIntBuffer(int id, int i){
	intEntry *temp = findIntEntry(id);
	if(NULL == temp)
		return 0;
	int *tempBufp = temp->buffer;
	while(tempBufp != temp->bufp){
		if(*tempBufp == i)
			return 1;
		tempBufp++;
	}
	return 0;
}


void memError(){
	fprintf(stderr, "memory error!\n");
}
