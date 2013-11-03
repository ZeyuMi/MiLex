#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"
#include "stringUtil.h"
#include "stack.h"

int isOperator(char);
int getPrecedence(char, int);
char *infixToPostfix(char *origin){	
	initialize();
	int pos = 0;
	char c;
	int doubleCharFlag = 0;
	while('\0' != (c = *(origin+pos))){
		if(isOperator(c)){
			if(EMPTY == top()){
				push(c);
			}else{
				if(')' == c){
					while('(' != top()){
						addElement(pop());
					}
					pop();	// pop '('
				}else{
					while(EMPTY != top() && getPrecedence(top(), 1) > getPrecedence(c, 0)){
						addElement(pop());
					}
					push(c);
				}
			}
		}else{
			addElement(c);
		}
		pos++;
	}
	while(EMPTY != top()){
		addElement(pop());
	}
	addElement('\0');
	char *s = getBuffer();
	char *result = malloc(strlen(s) + 1);
	strcpy(result, s);
	destroy();
	return result;
}


int isOperator(char c){
	if('*' == c)
		return 1;
	else if('@' == c)
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
	else if('@' == c)
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
