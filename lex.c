#include <stdio.h>
#include "lex.h"
#include "lexReader.h"
#include "nfaConstructor.h"
#include "dfaConstructor.h"
#include "dfaOptimizer.h"
#include "programGenerator.h"
#include "lexWriter.h"

char *declarations = NULL;
struct Defentry *definitions = NULL;
struct REentry *regexps = NULL;
struct Funcentry *additionalfuncs = NULL;

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
		constructNFA();
		constructDFA();
		optimizeDFA();
		generateProgram();
		writeProgram("lex.yy.c");
		return 0;
	}
}
