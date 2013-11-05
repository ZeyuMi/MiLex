#include <stdio.h>
#include "../nfaConstructor.h"

void testStackSuccessfully();
void testStackFailed();
void testStackDoubleSize();

int main(){
	testStackSuccessfully();
	testStackFailed();
	testStackDoubleSize();
	return 0;
}

void testStackSuccessfully(){
	struct NFASection a = {1,1};
	push(a);
	struct NFASection b = pop();
	printf("%d, %d\n", b.start, b.end);
}


void testStackFailed(){
	struct NFASection c = pop();
	printf("%d, %d\n", c.start, c.end);
}


void testStackDoubleSize(){
	struct NFASection a = {1,1};
	push(a);
	a.start = 2;
	a.end = 2;
	push(a);
	struct NFASection b = pop();
	printf("%d, %d\n", b.start, b.end);
	b = pop();
	printf("%d, %d\n", b.start, b.end);
}
