#include <stdlib.h>
#include <stdio.h>
#include "buffer.h"

#define DEFAULT 100 

static int buffersize = 0;

static char *buffer = NULL;
static char *bufp = NULL;

void memError();

void initialize(){
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
		buffer = realloc(buffer, buffersize);
		if(buffer == NULL)
			memError();
	}
	*bufp++ = c;
}


void addElements(char *s){
	while('\0' != *s){
		addElement(*s);
		s++;
	}
}


void destroy(){
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
