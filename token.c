#include<stdio.h>
#include<ctype.h>
#include"token.h"

#define BUFSIZE 100

enum states {
			STATE0 = 1,
			STATE1,
			STATE2,
			STATE3,
			STATE4,
			STATE5,
			STATE6,
			STATE7,
			STATE8,
			STATE9,
			};

int state = STATE0;

int getch();
void ungetch(int);
void error();
char token[TOKENSIZE];

int getToken(){
	state = STATE0;
	char *p = token;
	while(1){
		int c = getch();
		if(c == EOF)
			return c;
		switch(state){
			case STATE0:
				if(c == '/'){
					state = STATE1;
				}else if(c == ' ' || c == '\t'){
					state = STATE8;	
				}else if(c == '_' || isalpha(c)){
					state = STATE9;
					*p++ = c;
				}else{
					state = STATE0;
				}
				break;
			case STATE1:
				if(c == '*'){
					state = STATE2;
				}else if(c == '/'){
					state = STATE3;
				}else{
					*p++ = '/';
					*p = '\0';
					ungetch(c);
					return SLASH;
				}
				break;
			case STATE2:
				if(c == '*'){
					state = STATE4;
				}else{
					state = STATE2;
				}
				break;
			case STATE3:
				if(c == '\n'){
					state = STATE0;
				}else{
					state = STATE3;
				}
				break;
			case STATE4:
				if(c == '*'){
					state = STATE4;
				}else if(c == '/'){
					state = STATE0;
				}else{
					state = STATE2;
				}
				break;
			case STATE5:

				break;
			case STATE6:
				
				break;
			case STATE7:
				
				break;
			case STATE8:
				if(c == ' ' || c == '\t'){
					state = STATE8;
				}else{
					state = STATE0;
					ungetch(c);
				}
				break;
			case STATE9:
				if(c == '_' || isalnum(c)){
					state = STATE9;
					*p++ = c;
				}
				else{
					state = STATE0;
					*p = '\0';
					ungetch(c);
					return ID;
				}
				break;
			default:
				error();
		}
	}
}

void error(){
	printf("ERROR: entering wrong state\n");	
}

char buf[BUFSIZE];
int bufp = 0;

int getch(){
	return (bufp > 0) ? buf[bufp--] : getchar();
}

void ungetch(int c){
	if(bufp >= BUFSIZE-1)
		printf("ERROR: buffer is full\n");
	else
		buf[++bufp] = c;
}
