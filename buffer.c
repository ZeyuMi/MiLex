#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"

#define DEFAULT 100 

static int buffersize = 0;

static char *buffer = NULL;
static char *bufp = NULL;

void memError();

void initializeBuffer(){
	buffersize = DEFAULT;
	buffer = malloc(buffersize);
	if(buffer == NULL)
		memError();
	bufp = buffer;
}


char *getBuffer(){
	return buffer;
}


void addElement(char c){
	if(bufp - buffer >= buffersize){
		buffersize *= 2;
		char *old = buffer;
		buffer = malloc(buffersize);
		if(buffer == NULL)
			memError();
		memcpy((void *)buffer, (void *)old, buffersize/2);
		free(old);
		bufp = buffer + (buffersize/2);
	}
	*bufp++ = c;
}


void addElements(char *s){
	while('\0' != *s){
		addElement(*s);
		s++;
	}
}


void removeLast(){
	if(bufp == buffer)
		return;
	else
		bufp--;
}


void destroyBuffer(){
	buffersize = 0;
	free(buffer);
	buffer = bufp = NULL;
}


void rewindPointer(){
	bufp = buffer;
}

int size(){
	return bufp - buffer;
}

void memError(){
	fprintf(stderr, "memory error!\n");
	exit(EXIT_FAILURE);
}
