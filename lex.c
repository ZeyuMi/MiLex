#include <stdio.h>
#include "lex.h"
#include "lexReader.h"
#include "preprocessor.h"
#include "nfaConstructor.h"
#include "dfaConstructor.h"
#include "dfaOptimizer.h"
#include "programGenerator.h"
#include "lexWriter.h"

char *declarations = NULL;
struct Defentry *definitions = NULL;
struct REentry *regexps = NULL;
struct Funcentry *additionalfuncs = NULL;


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
//		output();
		preprocess();
		constructNFA();
		constructDFA();
		optimizeDFA();
		generateProgram();
		writeProgram("lex.yy.c");
//		output();
		return 0;
	}
}


void output(){
	struct Defentry *p = definitions;
	while(NULL != p){
		fprintf(stdout, "%s : %s\n", p->name, p->definition);
		p = p->next;
	}
	fprintf(stdout, "%s\n", declarations);
	struct REentry *e = regexps;
	while(NULL != e){
		fprintf(stdout, "%s : %s\n", e->regexp, e->action);
		e = e->next;
	}
	struct Funcentry *f = additionalfuncs;
	while(NULL != f){
		fprintf(stdout, "%s\n", f->body);
		f = f->next;
	}
}


