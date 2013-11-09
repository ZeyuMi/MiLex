#include <stdio.h>
#include "lex.h"
#include "lexReader.h"
#include "preprocessor.h"
#include "nfaConstructor.h"
#include "dfaConstructor.h"
#include "dfaOptimizer.h"
#include "programGenerator.h"

char *declarations = NULL;
struct Defentry *definitions = NULL;
struct REentry *regexps = NULL;
struct Funcentry *additionalfuncs = NULL;

char *charset = " !\\\"#$%&'\\(\\)\\*\\+,-./0123456789:;<=>\\?@ABCDEFGHIJKLMNOPQRSTUVWXYZ\\[\\\\\\]^_`abcdefghijklmnopqrstuvwxyz{\\|}~";

char *program = NULL;

void output();
int main(int argc, char **argv){
	if(1 == argc){
		fprintf(stderr, "MiLex needs one input file\n");
		return 1;
	}else{
		char *filename = *++argv;
		FILE *file = fopen(filename, "r");
		if(NULL == file){
			fprintf(stderr, "MiLex cannot read file %s\n", filename);
			return 1;
		}
		if(-1 == readFile(file)){
			fprintf(stderr, "the format of %s does not conform to MiLex\n", filename);
			return 1;
		}
		preprocess();
		output();
		constructNFA();
		constructDFA();
		optimizeDFA();
		generateProgram("lex.yy.c");
		return 0;
	}
}


void output(){
	struct Defentry *p = definitions;
	while(NULL != p){
		printf("%s : %s\n", p->name, p->definition);
		p = p->next;
	}
	printf("%s\n", declarations);
	struct REentry *e = regexps;
	while(NULL != e){
		printf("%s : %s\n", e->regexp, e->action);
		e = e->next;
	}
	struct Funcentry *f = additionalfuncs;
	while(NULL != f){
		printf("%s\n", f->body);
		f = f->next;
	}
}


