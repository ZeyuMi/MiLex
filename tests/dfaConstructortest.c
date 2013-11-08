#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../dfaConstructor.h"
#include "../nfaConstructor.h"
#include "../preprocessor.h"
#include "../lex.h"

char *declarations = NULL;
struct Defentry *definitions = NULL;
struct REentry *regexps = NULL;
struct Funcentry *additionalfuncs = NULL;
char *charset = " !\\\"#$%&'\\(\\)\\*\\+,-./0123456789:;<=>\\?@ABCDEFGHIJKLMNOPQRSTUVWXYZ\\[\\\\\\]^_`abcdefghijklmnopqrstuvwxyz{\\|}~";


void testConstructDFA1();
void testConstructDFA2();
void testConstructDFA3();

int main(){
	testConstructDFA1();
	testConstructDFA2();
	testConstructDFA3();
	return 0;
}


void testConstructDFA1(){
	regexps = malloc(sizeof(struct REentry));
	regexps->regexp = "1*|a";
	regexps->action = "printf;";
	constructNFA();
	constructDFA();
	printDFATransTable();
	destroyNFA();
	destroyDFA();
	destroyGraph();
}


void testConstructDFA2(){
	regexps = malloc(sizeof(struct REentry));
	char *s = "(a|b)*abb(a|b)*";
	regexps->regexp = malloc(strlen(s));
	strcpy(regexps->regexp, s);
	regexps->action = "printf;";
	regexps->next = NULL;
	preprocess();
	constructNFA();
	constructDFA();
	printDFATransTable();
	destroyDFA();
	destroyNFA();
	destroyGraph();
}


void testConstructDFA3(){
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
	regexps->next->next = NULL;
	preprocess();
	constructNFA();
	constructDFA();
	printDFATransTable();
	destroyNFA();
	destroyDFA();
	destroyGraph();
}

