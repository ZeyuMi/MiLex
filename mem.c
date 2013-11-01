/*
	naive memory management tool
	all the memory blocks should be returned in the reverse sequence where they are borrowed.
*/
#include "mem.h"

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n){
	if(allocbuf + ALLOCSIZE - allocp >= n){
		allocp += n;
		return allocp - n;
	}else{
		return 0;
	}
}

void afree(char *p){
	if(p > allocbuf && p< allocbuf + ALLOCSIZE)
		allocp = p;
}
