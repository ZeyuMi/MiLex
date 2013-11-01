#include<stdio.h>
#include"lexReader.h"
#include"lex.h"

FILE *in = NULL;
void readfromfile(char *filename){
	if(filename == NULL)
		return;
	FILE *file = fopen(filename, "r");
	if(file == NULL)
		return;
	in = file;

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
