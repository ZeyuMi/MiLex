#include <stdlib.h>
#include "stack.h"

#define DEFAULT 1

static char *stack = NULL;
static char *topp = NULL;
static int size;


char top(){
	if(NULL == stack){
		return EMPTY;
	}else if(topp == stack){
		return EMPTY;
	}else{
		return *(topp-1);
	}
}


char pop(){
	if(NULL == stack){
		return EMPTY;
	}else if(topp == stack){
		return EMPTY;
	}else{
		return *--topp;
	}
}


void push(char c){
	if(NULL == stack){
		size = DEFAULT;
		topp = stack = malloc(size);
	}else if(topp - stack >= size){
		char *old = stack;
		size *= 2;
		stack = malloc(size);
		memcpy(stack, old, size/2);
		free(old);
		topp = stack + (size/2);
	}
	*topp++ = c;
}
