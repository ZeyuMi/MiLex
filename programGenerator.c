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
	fprintf(file, "\n");
	fprintf(file, "void error(){");
	fprintf(file, "\tprintf(\"error!\\n\");");
	fprintf(file, "}");
	fprintf(file, "\n");

	struct Funcentry *funcTemp = additionalfuncs;
	while(NULL != funcTemp){
		fprintf(file, "\n");
		fprintf(file, "%s", funcTemp->body);
		fprintf(file, "\n");
		funcTemp = funcTemp->next;
	}
	fprintf(file, "\n");

	fprintf(file, "int yylex(){\n");
	
	fprintf(file, "\tstate = STATE0;");	
	fprintf(file, "\n");
	fprintf(file, "\tchar *p = yytext;");	
	fprintf(file, "\n");
	fprintf(file, "\twhile(1){");
	fprintf(file, "\n");
	
	fprintf(file, "\t\tint c = input();");
	fprintf(file, "\n");

	fprintf(file, "\t\tif(EOF == c)");
	fprintf(file, "\n");
	fprintf(file, "\t\t\treturn c;");
	fprintf(file, "\n");

	fprintf(file, "\t\tswitch(state){");
	fprintf(file, "\n");
	
	struct dfaTTEntry *entryTemp = getTable();
	while(NULL != entryTemp){
		i = 0;
		fprintf(file, "\t\t\tcase STATE%d:", entryTemp->state);
		fprintf(file, "\n");
		int hasIf = 0;
		while(i < 128){
			if(0 != (entryTemp->trans)[i]){
				hasIf = 1;
				fprintf(file, "\t\t\t\tif(\'%c\' == c){", i);
				fprintf(file, "\n");
				fprintf(file, "\t\t\t\t\tstate = STATE%d;", (entryTemp->trans)[i]);
				fprintf(file, "\n");
				fprintf(file, "\t\t\t\t\t*p++ = c;");
				fprintf(file, "\n");
				fprintf(file, "\t\t\t\t}");
				i++;
				break;
			}
			i++;
		}
		while(i < 128){
			if(0 != (entryTemp->trans)[i]){
				fprintf(file, "else if(\'%c\' == c){", i);
				fprintf(file, "\n");
				fprintf(file, "\t\t\t\t\tstate = STATE%d;", (entryTemp->trans)[i]);
				fprintf(file, "\n");
				fprintf(file, "\t\t\t\t\t*p++ = c;");
				fprintf(file, "\n");
				fprintf(file, "\t\t\t\t}");
			}
			i++;
		}
		if(hasIf){
			fprintf(file, "else{");
			fprintf(file, "\n");
			if(NULL != entryTemp->action){
				fprintf(file, "\t\t\t\t\t%s", entryTemp->action);
			}else{
				fprintf(file, "\t\t\t\t\terror();");
			}
			fprintf(file, "\n");
			fprintf(file, "\t\t\t\t}");
			fprintf(file, "\n");
		}else{
			if(NULL != entryTemp->action){
				fprintf(file, "\t\t\t\t\t%s", entryTemp->action);
			}else{
				fprintf(file, "\t\t\t\t\terror();");
			}
			fprintf(file, "\n");
		}
		fprintf(file, "\t\t\t\tbreak;");
		fprintf(file, "\n");
		entryTemp = entryTemp->next;
	}
	fprintf(file, "\t\t\tdefault:");
	fprintf(file, "\n");
	fprintf(file, "\t\t\t\terror();");
	fprintf(file, "\n");
	fprintf(file, "\t\t\t\tbreak;");
	fprintf(file, "\n");

	fprintf(file, "\t\t}");
	fprintf(file, "\n");
	fprintf(file, "\t}");
	fprintf(file, "\n");
	fprintf(file, "}");
	fprintf(file, "\n");
	fclose(file);
}
