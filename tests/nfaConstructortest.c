#include <stdio.h>
#include <stdlib.h>
#include "../lex.h"
#include "../graph.h"
#include "../nfaConstructor.h"

struct REentry *regexps = NULL;

void testConstructNFA();

int main(){
	testConstructNFA();
	return 0;
}

void testConstructNFA(){
	regexps = malloc(sizeof(struct REentry));
	regexps->regexp = "1*|a";
	regexps->action = "printf;";
	constructNFA();
	printGraph();
}

