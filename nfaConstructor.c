#include <stdio.h>
#include <stdlib.h>
#include "lex.h"
#include "nfaConstructor.h"
#include "stringUtil.h"
#include "graph.h"


int constructFromRE(char *);

int stateNum = 0;

void constructNFA(){
	struct REentry *retemp = regexps;
	int startPoint = ++stateNum;

	while(NULL != retemp){
		char *postfix = infixToPostfix(retemp->regexp);
		int childgraph = constructFromRE(postfix);
		addEdge(startPoint, childgraph, EPSILON);
		retemp = retemp->next;
	}
}


struct NFASection{
	int start;
	int end;
};


void push(struct NFASection);
struct NFASection pop();

int constructFromRE(char *postRE){
	int startPoint = ++stateNum;
	int pos = -1;
	char c;
	int start = end = -1;
	while(1){
		pos++;
		c = *(postRE+pos);
		if('\0' == c){
			temp = pop();
			return temp.start;
		}else if('|' == c){
			struct NFASection temp1 = pop();
			struct NFASection temp2 = pop();
			start = ++stateNum;
			end = ++stateNum;
			addVertex(start);
			addVertex(end);
			addEdge(start, temp1.start, EPSILON);
			addEdge(start, temp2.start, EPSILON);
			addEdge(temp2.end, end, EPSILON);
			addEdge(temp2.end, end, EPSILON);
			struct NFASection temp = {start, end};
			push(temp);
		}else if('?' == c){
			struct NFASection temp1 = pop();
			addEdge(temp1.start, temp1.end, EPSILON);
			push(temp1);
		}else if('+' == c){
			struct NFASection temp1 = pop();
			addEdge(temp1.end, temp1.start, EPSILON);
			push(temp1);
		}else if('*' == c){
			struct NFASection temp1 = pop();
			addEdge(temp1.end, temp1.start, EPSILON);
			start = ++stateNum;
			end = ++stateNum;
			addVertex(start);
			addVertex(end);
			addEdge(start, temp1.start, EPSILON);
			addEdge(temp1.end, end, EPSILON);
			addEdge(start, end, EPSILON);
			struct NFASection temp = {start, end};
			push(temp);
		}else if(CONSYMBOL == c){
		}else{
			start = ++stateNum;
			end = ++stateNum;
			addVertex(start);
			addVertex(end);
			addEdge(start. )
			addEdge(start, end, c);
			struct NFASection temp = {start, end};
			push(temp);
		}
	}
}

#define STACK_DEFAULT  100
struct NFASection *stack = NULL;
int topp = 0;
int stackSize = 0;

void push(struct NFASection n){
	if(NULL == stack){
		stackSize = STACK_DEFAULT;
		stack = (struct NFASection *)malloc(stackSize * sizeof(struct NFASection));
		topp = 0;
	}else if(topp == stackSize){
		stackSize *= 2;
		struct NFASection *old = stack;
		stack = (struct NFASection *)malloc(stackSize * sizeof(struct NFASection));
		memcpy(stack, old, (stackSize / 2) * sizeof(struct NFASection));
		free(old);
	}
	stack[topp++] = n;
}


struct NFASection pop(){
	if(topp == 0){
		struct NFASection t = {-1,-1};
		return t;
	}
	else
		return stack[--topp];
}
