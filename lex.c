#include <stdio.h>
#include "lex.h"
#include "lexReader.h"
#include "nfaConstructor.h"
#include "dfaConstructor.h"
#include "dfaOptimizer.h"
#include "programGenerator.h"
#include "lexWriter.h"

int main(int argc, char **argv){
	if(argc == 1){
		fprintf(stderr, "MiLex needs one input file\nUsage: ./MiLex filenam.l\n");
	}else{
		char *filename = *++argv;
		FILE *file = fopen(filename, "r");
		if(NULL == file){
			fprintf(stderr, "Error: %s cannot be opened.\n", filename);
			return 1;
		}
		int flag = readFile(file);
		if(flag == -1){
			fprintf(stderr, "MiLex cannot read %s\n", filename);
			return 1;
		}
		constructNFA();
		constructDFA();
		optimizeDFA();
		generateProgram();
		writeProgram("lex.yy.c");
	}
	return 0;
}
