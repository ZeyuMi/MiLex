#include <stdio.h>
#include <stdlib.h>
#include "lexReader.h"
#include "lex.h"

#define ERROR -1

enum states{STATE0 = 1,
			STATE1,
			STATE2,
			STATE3,
			STATE4,
			STATE5,
			STATE6,
			STATE7,
			STATE8,
			STATE9,
			STATE10,
			STATE11,
			};

FILE *in = NULL;

void readDeclareSec();
void readRESec();
void readFuncSec();

int readfromfile(FILE *file){
	if(file == NULL)
		return -1;
	in = file;
	if(ERROR == readDeclareSec())
		return -1;
	if(ERROR == readRESec())
		return -1;
	if(ERROR == readFuncSec())
		return -1;
	return 1;
}


void error();
int getch();
void ungetch(int c);

#define TOKENSIZE 100
char token[TOKENSIZE];

int readDeclareSec(){
	int state = STATE0;
	char *p = token;
	while(1){
		int c = getch();
		if(c == EOF)
			return ERROR;
		switch(state){
			case STATE0:
				if('/' == c){
					state = STATE1;
				}else if('%' == c){
					state = STATE9;
				}else if('\t' == c || ' ' == c || '\n' == c){
					state = STATE0;
				}else{
					state = STATE5;
					*p++ = c;
				}
				break;

			default:
				error();
		}
	}
}


void readRESec(){

}


void readFuncSec(){

}


void error(){
	fprintf(stderr, "Error: entering wrong states\n");
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(){
	return (bufp > 0) ? buf[bufp--] : getc(in);
}


void ungetch(int c){
	if(bufp >= BUFSIZE-1)
		printf("ERROR: buffer is full\n");
	else
		buf[++bufp] = c;
}
