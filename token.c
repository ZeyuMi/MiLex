#include<stdio.h>
#include<ctype.h>
#include"token.h"

#define BUFSIZE 100

#define STATE0 0
#define STATE1 1
#define STATE2 2

int state = STATE0;

int getch();
void ungetch(int);
void error();
char token[TOKENSIZE];

int getToken(){
	char *p = token;
	while(1){
		int c = getch();
		while(state == STATE0 && (c == ' ' || c == '\t'))
			c = getch();
		if(c == EOF)
			return c;
		switch(state){
			case STATE0:
				if(c == '_' || isalpha(c)){
					state = STATE1;
					*p++ = c;
				}
				break;
			case STATE1:
				if(c == '_' || isalnum(c)){
					state = STATE2;
					*p++ = c;
				}
				else{
					state = STATE0;
					*p = '\0';
					ungetch(c);
					return ID;
				}
				break;
			case STATE2:
				if(c == '_' || isalnum(c)){
					state = STATE2;
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
