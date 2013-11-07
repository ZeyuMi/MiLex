#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../lex.h"
#include "../graph.h"
#include "../nfaConstructor.h"
#include "../preprocessor.h"

char *declarations = NULL;
struct Defentry *definitions = NULL;
struct REentry *regexps = NULL;
struct Funcentry *additionalfuncs = NULL;


void testConstructNFA1();
void testConstructNFA2();
void testConstructNFA3();
void testConstructNFA4();
void testConstructNFA5();

int main(){
	testConstructNFA1();
	testConstructNFA2();
	testConstructNFA3();
	testConstructNFA4();
	testConstructNFA5();
	return 0;
}

void testConstructNFA1(){
	regexps = malloc(sizeof(struct REentry));
	regexps->regexp = "1*|a";
	regexps->action = "printf;";
	constructNFA();
	printGraph();
	destroyNFA();
}


void testConstructNFA2(){
	regexps = malloc(sizeof(struct REentry));
	char *s = "(a|b)*abb(a|b)*";
	regexps->regexp = malloc(strlen(s));
	strcpy(regexps->regexp, s);
	regexps->action = "printf;";
	preprocess();
	constructNFA();
	printGraph();
	destroyNFA();
}


void testConstructNFA3(){
	regexps = malloc(sizeof(struct REentry));
	char *s = "(a|b)*abb(a|b)*";
	regexps->regexp = malloc(strlen(s));
	strcpy(regexps->regexp, s);
	regexps->action = "printf;";
	regexps->next = malloc(sizeof(struct REentry));
	s = "(a|b)+abc(a|b|c)?";
	regexps->next->regexp = malloc(strlen(s));
	strcpy(regexps->next->regexp, s);
	regexps->next->action = "donothing";
	preprocess();
	constructNFA();
	printGraph();
	destroyNFA();
}


void testConstructNFA4(){
}


void testConstructNFA5(){
}

