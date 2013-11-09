#include <stdlib.h>
#include <string.h>
#include "lex.h"
#include "programGenerator.h"
#include "dfaTransTable.h"
#include "buffer.h"

void generateProgram(){
	int bufferid = initializeCharBuffer();
	addCharElements(bufferid, "#include <stdio.h>");
	addCharElement(bufferid, '\n');
	addCharElements(bufferid, declarations);
	addCharElement(bufferid, '\n');
	addCharElements(bufferid, "#define YYLMAX 200");
	addCharElement(bufferid, '\n');
	addCharElements(bufferid, "#define BUFSIZE 100");
	addCharElement(bufferid, '\n');
	addCharElements(bufferid, "enum states {");
	addCharElement(bufferid, '\n');
	
	int stateNum = getTableEntryNum();
	int i = 0;
	while(i <= stateNum){
		addCharElements(bufferid, "\t\tSTATE");
		addCharElement(bufferid, '0'+i);
		addCharElement(bufferid, ',');
		addCharElement(bufferid, '\n');
	}
	addCharElements(bufferid, "\t\t};");
	addCharElement(bufferid, '\n');
	addCharElements(bufferid, "int state = STATE0;");
	addCharElement(bufferid, '\n');

	addCharElements(bufferid, "FILE *yyin = stdin;");
	addCharElement(bufferid, '\n');
	addCharElements(bufferid, "FILE *yyout = stdout;");
	addCharElement(bufferid, '\n');
	addCharElements(bufferid, "char yytext[YYLMAX];");
	addCharElement(bufferid, '\n');
	addCharElements(bufferid, "int yyleng = 0;");
	addCharElement(bufferid, '\n');

	addCharElement(bufferid, '\n');
	addCharElements(bufferid, "char buf[BUFSIZE];");
	addCharElement(bufferid, '\n');
	addCharElements(bufferid, "int bufp = 0");
	addCharElement(bufferid, '\n');
	addCharElements(bufferid, "char input(){");
	addCharElement(bufferid, '\n');
	addCharElements(bufferid, "\treturn (bufp > 0) ? buf[bufp--] : getc(yyin);");
	addCharElement(bufferid, '\n');
	addCharElement(bufferid, '}');
	addCharElement(bufferid, '\n');
	addCharElements(bufferid, "void unput(int c){");
	addCharElement(bufferid, '\n');
	addCharElements(bufferid, "\tif(bufp >= BUFSIZE-1)");
	addCharElement(bufferid, '\n');
	addCharElements(bufferid, "\t\tfprintf(stderr, \"ERROR: BUFFER is full\\n\");");
	addCharElement(bufferid, '\n');
	addCharElements(bufferid, "\telse");
	addCharElement(bufferid, '\n');
	addCharElements(bufferid, "\t\tbuf[++bufp] = c;");
	addCharElement(bufferid, '\n');
	addCharElement(bufferid, '}');
	addCharElement(bufferid, '\n');





	addCharElements(bufferid, "int yylex(){\n");
	
	addCharElements(bufferid, "}\n");

	addCharElement(bufferid, '\0');
	program = malloc(charSize(bufferid));
	strcpy(program, getCharBuffer(bufferid));
	destroyCharBuffer(bufferid);
}
