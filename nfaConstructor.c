#include <stdio.h>
#include "lex.h"
#include "nfaConstructor.h"
#include "stringUtil.h"

void constructNFA(){
	struct REentry *retemp = regexps;
	while(NULL != retemp){
		char *postfix = infixToPostfix(retemp->regexp);
		printf("%s\n", postfix);
		retemp = retemp->next;
	}
}


