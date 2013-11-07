#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"

#define DEFAULT 100 

static int charBuffersize = 0;
static int intBuffersize = 0;

static char *charBuffer = NULL;
static char *charBufp = NULL;

static int *intBuffer = NULL;
static int *intBufp = NULL;

void memError();

void initializeCharBuffer(){
	charBuffersize = DEFAULT;
	charBuffer = malloc(charBuffersize);
	if(charBuffer == NULL)
		memError();
	charBufp = charBuffer;
}

void initializeIntBuffer(){
	intBuffersize = DEFAULT;
	intBuffer = malloc(sizeof(int) * intBuffersize);
	if(intBuffer == NULL)
		memError();
	intBufp = intBuffer;
}

char *getCharBuffer(){
	return charBuffer;
}


void addCharElement(char c){
	if(charBufp - charBuffer >= charBuffersize){
		charBuffersize *= 2;
		char *old = charBuffer;
		charBuffer = malloc(charBuffersize);
		if(charBuffer == NULL)
			memError();
		memcpy((void *)charBuffer, (void *)old, charBuffersize/2);
		free(old);
		charBufp = charBuffer + (charBuffersize/2);
	}
	*charBufp++ = c;
}


void addIntElement(int i){
	if(intBufp - intBuffer >= intBuffersize){
		intBuffersize *= 2;
		int *old = intBuffer;
		intBuffer = malloc(sizeof(int) * intBuffersize);
		if(intBuffer == NULL)
			memError();
		memcpy((void *)charBuffer, (void *)old, sizeof(int) * (charBuffersize/2));
		free(old);
		intBufp = intBuffer + (charBuffersize/2);
	}
	*intBufp++ = i;
}


void addCharElements(char *s){
	while('\0' != *s){
		addCharElement(*s);
		s++;
	}
}


void removeCharLast(){
	if(charBufp == charBuffer)
		return;
	else
		charBufp--;
}


void removeIntLast(){
	if(intBufp == intBuffer)
		return;
	else
		intBufp--;
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


void memError(){
	fprintf(stderr, "memory error!\n");
	exit(EXIT_FAILURE);
}
