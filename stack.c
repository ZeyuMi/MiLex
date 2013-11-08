#include <stdlib.h>
#include "stack.h"

#define DEFAULT 1

static int *stack = NULL;
static int *topp = NULL;
static int size;


int topStack(){
	if(NULL == stack){
		return EMPTY;
	}else if(topp == stack){
		return EMPTY;
	}else{
		return *(topp-1);
	}
}


int popStack(){
	if(NULL == stack){
		return EMPTY;
	}else if(topp == stack){
		return EMPTY;
	}else{
		return *--topp;
	}
}


void pushStack(int c){
	if(NULL == stack){
		size = DEFAULT;
		topp = stack = malloc(size * sizeof(int));
	}else if(topp - stack >= size){
		int *old = stack;
		size *= 2;
		stack = malloc(size * sizeof(int));
		memcpy(stack, old, sizeof(int) * (size/2));
		free(old);
		topp = stack + (size/2);
	}
	*topp++ = c;
}


void clearStack(){
	while(EMPTY != popStack())
		;
}
