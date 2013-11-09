#include <stdio.h>
#include "lex.h"
#include "lexWriter.h"

void writeProgram(char *filename){
	FILE *file = fopen(filename, "w");
	fprintf(file, program);
	fclose(file);
}

