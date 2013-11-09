#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.h"
#include "programGenerator.h"
#include "dfaTransTable.h"

void generateProgram(char *filename){
	FILE *file = fopen(filename, "w");

	fprintf(file, "#include <stdio.h>");
	fprintf(file, "\n");
	fprintf(file, "%s", declarations);
	fprintf(file, "\n");
	fprintf(file, "#define YYLMAX 200");
	fprintf(file, "\n");
	fprintf(file, "#define BUFSIZE 100");
	fprintf(file, "\n");
	fprintf(file, "enum states {");
	fprintf(file, "\n");
	
	int stateNum = getTableEntryNum();
	int i = 0;
	while(i <= stateNum){
		fprintf(file, "\t\tSTATE");
		fprintf(file, "%d", i);
		fprintf(file, ",");
		fprintf(file, "\n");
		i++;
	}
	fprintf(file, "\t\t};");
	fprintf(file, "\n");
	fprintf(file, "int state = STATE0;");
	fprintf(file, "\n");

	fprintf(file, "FILE *yyin = stdin;");
	fprintf(file, "\n");
	fprintf(file, "FILE *yyout = stdout;");
	fprintf(file, "\n");
	fprintf(file, "char yytext[YYLMAX];");
	fprintf(file, "\n");
	fprintf(file, "int yyleng = 0;");
	fprintf(file, "\n");

	fprintf(file, "\n");
	fprintf(file, "char buf[BUFSIZE];");
	fprintf(file, "\n");
	fprintf(file, "int bufp = 0");
	fprintf(file, "\n");
	fprintf(file, "char input(){");
	fprintf(file, "\n");
	fprintf(file, "\treturn (bufp > 0) ? buf[bufp--] : getc(yyin);");
	fprintf(file, "\n");
	fprintf(file, "\n");
	fprintf(file, "}");
	fprintf(file, "\n");
	fprintf(file, "\n");
	fprintf(file, "void unput(int c){");
	fprintf(file, "\n");
	fprintf(file, "\tif(bufp >= BUFSIZE-1)");
	fprintf(file, "\n");
	fprintf(file, "\t\tfprintf(stderr, \"ERROR: BUFFER is full\\n\");");
	fprintf(file, "\n");
	fprintf(file, "\telse");
	fprintf(file, "\n");
	fprintf(file, "\t\tbuf[++bufp] = c;");
	fprintf(file, "\n");
	fprintf(file, "}");
	fprintf(file, "\n");





	fprintf(file, "int yylex(){\n");
	
	fprintf(file, "}\n");
	fclose(file);
}
