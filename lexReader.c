#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexReader.h"
#include "lex.h"
#include "buffer.h"
#include "error.h"

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
			STATE12,
			};

FILE *in = NULL;

int readDeclareSec();
int readRESec();
int readFuncSec();

int readFile(FILE *file){
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


int getch();
void ungetch(int );
void insertDefEntry(char *);
void insertDefContent(char *);
void insertREEntry(char *);
void insertREAction(char *);
void insertFuncEntry(char *);


struct Defentry *defp = NULL;
int readDeclareSec(){
	initializeBuffer();
	int state = STATE0;
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
					addElement(c);
				}
				break;
			case STATE1:
				if('*' == c){
					state = STATE2;
				}else if('/' == c){
					state = STATE4;
				}else if(' ' == c || '\t' == c||'\n' == c){
					error("lexReader readDeclareSec STATE1");
				}else{
					state = STATE5;
					addElement(c);
				}
				break;
			case STATE2:
				if('*' == c){
					state = STATE3;
				}else{
					state = STATE2;
				}
				break;
			case STATE3:
				if('*' == c){
					state = STATE3;
				}else if('/' == c){
					state = STATE0;
				}else{
					state = STATE2;
				}
				break;
			case STATE4:
				if('\n' == c){
					state = STATE0;
				}else{
					state = STATE4;
				}
				break;
			case STATE5:
				if(' ' == c || '\t' == c){
					state = STATE6;
					addElement('\0');
					insertDefEntry(getBuffer());
					rewindPointer();
				}else if('\n' == c){
					error("lexReader readDeclareSec STATE5");
				}else{
					state = STATE5;
					addElement(c);
				}
				break;
			case STATE6:
				if(' ' == c || '\t' == c){
					state = STATE6;
				}else if('\n' == c){
					error("lexReader readDeclareSec STATE6");
				}else{
					state = STATE7;
					ungetch(c);
				}
				break;
			case STATE7:
				if(' ' == c || '\t' == c || '\n' == c){
					state = STATE0;
					addElement('\0');
					insertDefContent(getBuffer());
					rewindPointer();
				}else if('\"' == c || '[' == c){
					state = STATE8;
					addElement(c);
				}else{
					state = STATE7;
					addElement(c);
				}
				break;
			case STATE8:
				if('\"' == c || ']' == c){
					state = STATE7;
					addElement(c);
				}else if('\n' == c || '\t' == c){
					error("lexReader readDeclareSec STATE8");
				}else{
					state = STATE8;
					addElement(c);
				}
				break;
			case STATE9:
				if('{' == c){
					state = STATE10;
				}else if('%' == c){
					state = STATE0;
					destroyBuffer();
					return 1;
				}else{
					error("lexReader readDeclareSec STATE9");
				}
				break;
			case STATE10:
				if('%' == c){
					state = STATE11;
				}else{
					state = STATE10;
					addElement(c);
				}
				break;
			case STATE11:
				if('}' == c){
					state = STATE0;
				    declarations = malloc(size());
					strcpy(declarations, getBuffer());
					rewindPointer();
				}else{
					error("lexReader readDeclareSec STATE11");
				}
				break;
			default:
				error("entering wrong state");
		}
	}
}

struct REentry *rep = NULL;
int readRESec(){
	initializeBuffer();
	int state = STATE0;
	while(1){
		char c = getch();
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
					ungetch(c);
				}
				break;
			case STATE1:
				if('*' == c){
					state = STATE2;
				}else if('/' == c){
					state = STATE4;
				}else if(' ' == c || '\t' == c||'\n' == c){
					error("lexReader readRESec STATE1");
				}else{
					state = STATE5;
					ungetch(c);
				}
				break;
			case STATE2:
				if('*' == c){
					state = STATE3;
				}else{
					state = STATE2;
				}
				break;
			case STATE3:
				if('*' == c){
					state = STATE3;
				}else if('/' == c){
					state = STATE0;
				}else{
					state = STATE2;
				}
				break;
			case STATE4:
				if('\n' == c){
					state = STATE0;
				}else{
					state = STATE4;
				}
				break;
			case STATE5:
				if(' ' == c || '\t' == c){
					state = STATE7;
					addElement('\0');
					insertREEntry(getBuffer());
					rewindPointer();
				}else if('\n' == c){
					error("lexReader readRESec STATE5");
				}else if('\"' == c || '[' == c){
					state = STATE6;
					addElement(c);
				}else{
					state = STATE5;
					addElement(c);
				}
				break;
			case STATE6:
				if('\"' == c || ']' == c){
					state = STATE5;
					addElement(c);
				}else if('\n' == c || '\t' == c){
					error("lexReader readRESec STATE6");
				}else{
					state = STATE6;
					addElement(c);
				}
				break;
			case STATE7:
				if(' ' == c || '\t' == c){
					state = STATE7;
				}else if('{' == c){
					state = STATE8;
				}else{
					error("lexReader readRESec STATE7");
				}
				break;
			case STATE8:
				if('}' == c){
					state = STATE0;
					addElement('\0');
					insertREAction(getBuffer());
					rewindPointer();
				}else{
					state = STATE8;
					addElement(c);
				}
				break;
			case STATE9:
				if('%' == c){
					state = STATE0;
					destroyBuffer();
					return 1;
				}
				break;
			defualt:
				error("entering wrong state");
		}
	}
}

struct Funcentry *funcp = NULL;
int readFuncSec(){
	int leftBraceNum = 0;
	initializeBuffer();
	int state = STATE0;
	while(1){
		char c = getch();
		if(c == EOF){
			if(state != STATE0)
				return ERROR;
			else{
				destroyBuffer();
				return 1;
			}
		}
		switch(state){
			case STATE0:
				if('/' == c){
					state = STATE1;
				}else if(isalpha(c) || '_' == c){
					state = STATE5;
					leftBraceNum = 0;
					addElement(c);
				}else if('\t' == c || ' ' == c || '\n' == c){
					state = STATE0;
				}else{
					error("lexReader readFuncSec state0");
				}
				break;
			case STATE1:
				if('*' == c){
					state = STATE2;
				}else if('/' == c){
					state = STATE4;
				}else{
					error("lexReader readFuncSec state1");
				}
				break;
			case STATE2:
				if('*' == c){
					state = STATE3;
				}else{
					state = STATE2;
				}
				break;
			case STATE3:
				if('*' == c){
					state = STATE3;
				}else if('/' == c){
					state = STATE0;
				}else{
					state = STATE2;
				}
				break;
			case STATE4:
				if('\n' == c){
					state = STATE0;
				}else{
					state = STATE4;
				}
				break;
			case STATE5:
				if('\"' == c){
					state = STATE6;
					addElement(c);
				}else if('{' == c){
					state = STATE5;
					leftBraceNum++;
					addElement(c);
				}else if('/' == c){
					state = STATE7;
					addElement(c);
				}else if(c == '}'){
					leftBraceNum--;
					addElement(c);
					if(0 == leftBraceNum){
						state = STATE0;
						addElement('\0');
						insertFuncEntry(getBuffer());
						rewindPointer();
					}else{
						state = STATE5;
					}
				}else{
					state = STATE5;
					addElement(c);
				}
				break;
			case STATE6:
				addElement(c);
				if('\"' == c){
					state = STATE5;
				}else if('\n' == c){
					error("lexReader readFuncSec state6");
				}else{
					state = STATE6;
				}
				break;
			case STATE7:
				addElement(c);
				if('*' == c){
					state = STATE8;
				}else if('/' == c){
					state = STATE10;
				}else{
					error("lexReader readFuncSec state7");
				}
				break;
			case STATE8:
				addElement(c);
				if('*' == c){
					state = STATE9;
				}else{
					state = STATE8;
				}
				break;
			case STATE9:
				addElement(c);
				if('*' == c){
					state = STATE9;
				}else if('/' == c){
					state = STATE5;
				}else{
					state = STATE8;
				}
				break;
			case STATE10:
				addElement(c);
				if('\n' == c){
					state = STATE5;
				}else{
					state = STATE10;
				}
				break;
			default:
				error("entering wrong state.");
		}
	}
}


void insertDefEntry(char *name){
	struct Defentry *temp = malloc(sizeof(struct Defentry));
	if(NULL == definitions){
		definitions = defp = temp;			
	}else{
		defp->next = temp;
		defp = temp;
	}
	temp->name = malloc(strlen(name)+1);
	strcpy(temp->name, name);
	temp->definition = NULL;
	temp->next = NULL;
}


void insertDefContent(char *def){
	defp->definition = malloc(strlen(def)+1);
	strcpy(defp->definition, def);
}


void insertREEntry(char *re){
	struct REentry *temp = malloc(sizeof(struct REentry));
	if(NULL == regexps){
		regexps = rep = temp;			
	}else{
		rep->next = temp;
		rep = temp;
	}
	temp->regexp = malloc(strlen(re)+1);
	strcpy(temp->regexp, re);
	temp->action = NULL;
	temp->next = NULL;
}


void insertREAction(char *action){
	rep->action = malloc(strlen(action)+1);
	strcpy(rep->action, action);
}


void insertFuncEntry(char *body){
	struct Funcentry *temp = malloc(sizeof(struct Funcentry));
	if(NULL == additionalfuncs){
		additionalfuncs = funcp = temp;			
	}else{
		funcp->next = temp;
		funcp = temp;
	}
	temp->body = malloc(strlen(body)+1);
	strcpy(temp->body, body);
	temp->next = NULL;
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
