#include <stdio.h>
#include "lex.h"
#include "nfaConstructor.h"
#include "stringUtil.h"
#include "graph.h"

struct NFASection{
	int start;
	int end;
};

int constructFromRE(char *);

int stateNum = 0;

void constructNFA(){
	struct REentry *retemp = regexps;
	int startPoint = ++stateNum;

	while(NULL != retemp){
		char *postfix = infixToPostfix(retemp->regexp);
		int childgraph = constructFromRE(postfix);
		addEdge(startPoint, childgraph);
		retemp = retemp->next;
	}
}


void push(struct NFASection);
struct NFASection pop();

int constructFromRE(char *postRE){
	int startPoint = ++stateNum;
	int pos = -1;
	char c;
	struct vertex *result;
	struct vertex *temp1;

	while(1){
		pos++;
		c = *(postRE+pos);
		if('|' == c){
			
		}else if('?' == c){

		}else if('+' == c){

		}else if('*' == c){

		}else if(CONSYMBOL == c){
			result = connectVertexes(v1, v2, EPSILON);
		}else{
			struct vertex *v1 = getNewVertex();
			struct vertex *v2 = getNewVertex();
			if(NULL == result)
				result = connectVertexes(v1, v2, c);
			else
				temp = connectVertexes(v1, v2, c);
		}
	}
}

#define STACK_DEFAULT 100
struct NFASection *stack = NULL;
struct NFASection *topp = NULL;
int stackSize = 0;

void push(struct NFASection n){
	if(NULL == stack){
		stackSize = STACK_DEFAULT;
		topp = stack = (struct NFASection *)malloc(stackSize * sizeof(struct NFASection));
	}else if(topp - stack == stackSize){
		stackSize *= 2;
		struct NFASection *old = stack;
		stack = (struct NFASection *)malloc(stackSize * sizeof(struct NFASection));
		memcpy(stack, old, (stackSize / 2) * sizeof(struct NFASection));
		topp = stack + stackSize;
	}
	topp++ = &n;
}


struct NFASection pop(){

}
