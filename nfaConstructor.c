#include <stdio.h>
#include "lex.h"
#include "nfaConstructor.h"
#include "stringUtil.h"
#include "graph.h"


struct vertex *constructFromRE(char *);

void constructNFA(){
	struct REentry *retemp = regexps;
	struct vertex *startPoint = getNewVertex();
	while(NULL != retemp){
		char *postfix = infixToPostfix(retemp->regexp);
		struct vertex *v = constructFromRE(postfix);
		connectVertexes(startPoint, v, EPSILON);
		retemp = retemp->next;
	}
}


struct vertex *constructFromRE(char *postRE){
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


static int stateNum = 0;
struct vertex *getNewVertex(){
	return createVertex(++stateNum, EPSILON, NULL);
}
