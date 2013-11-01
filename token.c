#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
			STATE10,
			STATE11,
			STATE12,
			STATE13,
			STATE14,
			STATE15,
			STATE16,
			STATE17,
			};

int state = STATE0;

static struct tabentry *idtable = NULL;
static struct tabentry *idp = NULL;
static int idnumnow = 0;
static struct tabentry *optable = NULL;
static struct tabentry *opp = NULL;
static int opnumnow = 0;
int installID();
int installOP();
int getch();
void ungetch(int);
void error();
void outputtable(char *, struct tabentry *);

char yytext[TOKENSIZE];
int yyleng;
int yylval;
FILE *in;

void setIn(FILE *inputFile){
	in = inputFile;
}

void unsetIn(){
	in = NULL;
	outputtable("idtable", idtable);
	outputtable("optable", optable);
	idtable = idp = optable = opp = NULL;
	idnumnow = opnumnow = 0;
}

int getToken(){
	state = STATE0;
	char *p = yytext;
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
				}else if(isdigit(c)){
					state = STATE10;
					*p++ = c;
				}else if(c == '.'){
					state = STATE11;
					*p++ = c;
				}else if(c == '='){
					state = STATE12;
					*p++ = c;
				}else if(c == '>'){
					state = STATE13;
					*p++ = c;
				}else if(c == '<'){
					state = STATE14;
					*p++ = c;
				}else if(c == '+'){
					state = STATE15;
					*p++ = c;
				}else if(c == '-'){
					state = STATE16;
					*p++ = c;
				}else if(c == '*' || c == '%'){
					state = STATE17;
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
				}else if(c == '='){
					state = STATE17;
					*p++ = '/';
					*p++ = '=';
					*p = '\0';
					yylval = installOP();
					return OP;
				}else{
					state = STATE0;
					*p++ = '/';
					*p = '\0';
					ungetch(c);
					yylval = installOP();
					return OP;
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
					yylval = installID();
					return ID;
				}
				break;
			case STATE10:
				if(isdigit(c)){
					state = STATE10;
					*p++ = c;
				}else if(c == '.'){
					state = STATE11;
					*p++ = c;
				}else{
					state = STATE0;
					*p = '\0';
					ungetch(c);
					return NUMBER;
				}
				break;
			case STATE11:
				if(isdigit(c)){
					state = STATE11;
					*p++ = c;
				}else{
					state = STATE0;
					*p = '\0';
					ungetch(c);
					return NUMBER;
				}
				break;
			case STATE12:
				if(c == '='){
					state = STATE0;
					*p++ = c;
					*p = '\0';
					yylval = installOP();
					return OP;
				}else{
					state = STATE0;
					*p = '\0';
					ungetch(c);
					return ASSIGN;
				}
				break;
			case STATE13:
				if(c == '>'){
					state = STATE0;
					*p++ = c;
					*p = '\0';
					yylval = installOP();
					return OP;
				}else if(c == '='){
					state = STATE0;
					*p++ = c;
					*p = '\0';
					yylval = installOP();
					return OP;
				}else{
					state = STATE0;
					*p = '\0';
					ungetch(c);
					yylval = installOP();
					return OP;
				}
				break;
			case STATE14:
				if(c == '<'){
					state = STATE0;
					*p++ = c;
					*p = '\0';
					yylval = installOP();
					return OP;
				}else if(c == '='){
					state = STATE0;
					*p++ = c;
					*p = '\0';
					yylval = installOP();
					return OP;
				}else{
					state = STATE0;
					*p = '\0';
					ungetch(c);
					yylval = installOP();
					return OP;
				}
				break;
			case STATE15:
				if(c == '='){
					state = STATE0;
					*p++ = c;
					*p = '\0';
					yylval = installOP();
					return OP;
				}else if(c == '+'){
					state = STATE0;
					*p++ = c;
					*p = '\0';
					yylval = installOP();
					return OP;
				}else{
					state = STATE0;
					*p = '\0';
					ungetch(c);
					yylval = installOP();
					return OP;
				}
				break;
			case STATE16:
				if(c == '='){
					state = STATE0;
					*p++ = c;
					*p = '\0';
					yylval = installOP();
					return OP;
				}else if(c == '-'){
					state = STATE0;
					*p++ = c;
					*p = '\0';
					yylval = installOP();
					return OP;
				}else{
					state = STATE0;
					*p = '\0';
					ungetch(c);
					yylval = installOP();
					return OP;
				}
				break;
			case STATE17:
				if(c == '='){
					state = STATE0;
					*p++ = c;
					*p = '\0';
					yylval = installOP();
					return OP;
				}else{
					state = STATE0;
					*p = '\0';
					ungetch(c);
					yylval = installOP();
					return OP;
				}
				break;
			default:
				error();
		}
	}
}


int installID(){
	struct tabentry *temp = malloc(sizeof(struct tabentry));
	temp->sequnceid = ++idnumnow;
	temp->lexem = malloc(strlen(yytext)+1);
	strcpy(temp->lexem, yytext);
	if(idtable == NULL){
		idtable = idp = temp;
		idtable->next = NULL;
	}else{
		idp->next = temp;
		idp = temp;
		idp->next = NULL;
	}
	return idnumnow;
}


int installOP(){	
	struct tabentry *temp = malloc(sizeof(struct tabentry));
	temp->sequnceid = ++opnumnow;
	temp->lexem = malloc(strlen(yytext)+1);
	strcpy(temp->lexem, yytext);
	if(optable == NULL){
		optable = opp = temp;
		optable->next = NULL;
	}else{
		opp->next = temp;
		opp = temp;
		opp->next = NULL;
	}
	return opnumnow;
}

void outputtable(char *tabname, struct tabentry *tabhead){
	char *filename = tabname;
	FILE *file = fopen(filename, "w");
	fprintf(file, "%s,%s\n", "id", "lexem");
	struct tabentry *p = tabhead;
	struct tabentry *pre = NULL;
	while(p != NULL){
		fprintf(file, "%d,%s\n", p->sequnceid, p->lexem);
		pre = p;
		p = p->next;
		free(pre);
	}
	tabhead = NULL;
	fclose(file);
}


void error(){
	printf("ERROR: entering wrong state\n");	
}


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
