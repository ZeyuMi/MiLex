#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"
#include "stringUtil.h"
#include "stack.h"
#include "lex.h"

int isOperator(char);
int getPrecedence(char, int);
char *infixToPostfix(char *origin){	
	initializeBuffer();
	int pos = 0;
	char c;
	int doubleCharFlag = 0;
	while('\0' != (c = *(origin+pos))){
		if(isOperator(c)){
			if(EMPTY == topStack()){
				pushStack(c);
			}else{
				if(')' == c){
					while('(' != topStack()){
						addElement(popStack());
					}
					popStack();	// pop '('
				}else{
					while(EMPTY != topStack() && getPrecedence(topStack(), 1) >= getPrecedence(c, 0)){
						addElement(popStack());
					}
					pushStack(c);
				}
			}
		}else{
			addElement(c);
		}
		pos++;
	}
	while(EMPTY != topStack()){
		addElement(popStack());
	}
	addElement('\0');
	char *s = getBuffer();
	char *result = malloc(strlen(s) + 1);
	strcpy(result, s);
	destroyBuffer();
	return result;
}


int isOperator(char c){
	if('*' == c)
		return 1;
	else if(CONSYMBOL == c)
		return 1;
	else if('|' == c)
		return 1;
	else if('?' == c)
		return 1;
	else if('+' == c)
		return 1;
	else if('(' == c)
		return 1;
	else if(')' == c)
		return 1;
	else 
		return 0;
}


int getPrecedence(char c, int instack){
	if('?' == c || '+' == c || '*' == c)
		return 10;
	else if(CONSYMBOL == c)
		return 5;
	else if('|' == c)
		return 1;
	else if('(' == c){
		if(instack)
			return 0;
		else
			return 11;
	}else
		return -1;
}
