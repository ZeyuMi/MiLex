#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lex.h"
#include "nfaConstructor.h"
#include "buffer.h"

void preprocess();

void constructNFA(){
	preprocess();	

}

void replaceAllDef();
void substitute();


void preprocess(){
	replaceAllDef();
	substitute();
}


char *replace(char *, char *, char *);


/*replace all the definitions in subsequent definitions and regular expressions*/
void replaceAllDef(){
	struct Defentry *dp = definitions;
	while(NULL != dp){
		int namelen = strlen(dp->name);
		char *temp = malloc(namelen+3);
		strncpy(temp+1, dp->name, namelen);
		*temp = '{';
		*(temp+namelen+1) = '}';
		*(temp+namelen+2) = '\0';
		struct Defentry *deftemp = dp->next;
		while(NULL != deftemp){
			deftemp->definition = replace(deftemp->definition, temp, dp->definition);
			deftemp = deftemp->next;
		}
		/*now replace definition in regular expressions*/
		struct REentry *retemp = regexps;
		while(NULL != retemp){
			retemp->regexp = replace(retemp->regexp, temp, dp->definition);
			retemp = retemp->next;
		}
		dp = dp->next;
	}
}


char *substituteCharClass(char *);
char *substituteQuesSymbol(char *);


/*substitute character class and question symbol with its correspoinding characters*/
void substitute(){
	struct REentry *retemp = regexps;
	while(NULL != retemp){
		retemp->regexp = substituteCharClass(retemp->regexp);
		retemp->regexp = substituteQuesSymbol(retemp->regexp);
		retemp = retemp->next;
	}
}


char *replace(char *origin, char *rep, char *with){
	char *op = origin;
	int replen = strlen(rep);
	int withlen = strlen(with);
	if(NULL == origin || NULL == rep || NULL == with){
		return NULL;
	}
	int count = 0;
	while(NULL != (op = strstr(op, rep))){
		count++;
		op += replen;
	}
	
	op = origin;
	char *result = malloc(strlen(origin) + count * (withlen - replen) + 1);
	char *np = result;
	char *left = NULL;
	int i;
	for(i = 0; i < count; i++){
		left = strstr(op, rep);
		strncpy(np, op, left-op);
		np += (left-op);
		op += (left-op);
		strncpy(np, with, withlen);
		np += withlen;
		op += replen;
	}
	strcpy(np,op);
	free(origin);
	return result;
}


enum states{ STATE0 = 1,
				STATE1,
				STATE2,
				STATE3,
				STATE4,
				STATE5,
				STATE6,
				STATE7,
				STATE8,
				};
char *getStr(char *);
void error1();

char *substituteCharClass(char *origin){
	initialize();
	int pos = -1;
	int orilen = strlen(origin);
	int state = STATE0;
	char buf[3] = {0};
	while(1){
		pos++;
		if(pos >= orilen)
			break;
		char c = *(origin+pos);
		switch(state){
			case STATE0:
				if('[' == c){
					state = STATE1;
					addElement(c);
				}else if('\\' == c){
					state = STATE8;
					addElement(c);
				}else{
					state = STATE0;
					addElement(c);
				}
				break;
			case STATE1:
				if(']' == c){
					state = STATE0;
					addElement(c);
				}else if('A' <= c && 'Z' >= c){
					state = STATE2;
					buf[0] = c;
				}else if('a' <= c && 'z' >= c){
					state = STATE4;
					buf[0] = c;
				}else if('0' <= c && '9' >= c){
					state = STATE6;
					buf[0] = c;
				}else{
					state = STATE1;
					addElement(c);
				}
				break;
			case STATE2:
				if('-' == c){
					state = STATE3;
					buf[1] = c;
				}else{
					state = STATE1;
					addElement(buf[0]);
					pos--;
				}
				break;
			case STATE3:
				state = STATE1;
				if('A' <= c && 'Z' >= c){
					buf[2] = c;
					char *s = getStr(buf);
					addElements(s);
					free(s);
				}else{
					addElement(buf[0]);
					addElement(buf[1]);
					pos--;
				}
				break;
			case STATE4:
				if('-' == c){
					state = STATE5;
					buf[1] = c;
				}else{
					state = STATE1;
					addElement(buf[0]);
					pos--;
				}
				break;
			case STATE5:
				state = STATE1;
				if('a' <= c && 'z' >= c){
					buf[2] = c;
					char *s = getStr(buf);
					addElements(s);
					free(s);
				}else{
					addElement(buf[0]);
					addElement(buf[1]);
					pos--;
				}
				break;
			case STATE6:
				if('-' == c){
					state = STATE7;
					buf[1] = c;
				}else{
					state = STATE1;
					addElement(buf[0]);
					pos--;
				}
				break;
			case STATE7:
				state = STATE1;
				if('0' <= c && '9' >= c){
					buf[2] = c;
					char *s = getStr(buf);
					addElements(s);
					free(s);
				}else{
					addElement(buf[0]);
					addElement(buf[1]);
					pos--;
				}
				break;
			case STATE8:
				state = STATE0;
				addElement(c);
				break;
			default:
				error1();
		}
	}
	free(origin); // free the origin string
	addElement('\0');
	char *s = getBuffer();
	char *result = malloc(strlen(s) + 1);
	strcpy(result, s);
	destroy();
	return result;
}

char *charTable[3]= {
					"ABCDEFGHIJKLMNOPQRSTUVWXYZ",
					"abcdefghijklmnopqrstuvwxyz",
					"0123456789"
					};


char *getStr(char *buf){
	char *s = malloc(abs(buf[2] - buf[0]) + 2);
	int pos = 0;
	int type = 0;
	if('A' <= buf[0] && 'Z' >= buf[2])
		type = 0;
	else if('a' <= buf[0] && 'z' >= buf[2])
		type = 1;
	else
		type = 2;
	int start = buf[0] - charTable[type][0];
	int end = buf[2] - charTable[type][0];
	while(start != end){
		s[pos++] = charTable[type][start];
		if(start < end)
			start++;
		else
			start--;
	}
	s[pos++] = charTable[type][start];
	s[pos] = '\0';
	return s;
}


void error1(){
	fprintf(stderr, "entering wrong state\n");
}

char *substituteQuesSymbol(char *origin){
	return origin;
}
