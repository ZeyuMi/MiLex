%{
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "token.h"

int yylval;
static struct tabentry *idtable = NULL;
static struct tabentry *idp = NULL;
static int idnumnow = 0;
static struct tabentry *optable = NULL;
static struct tabentry *opp = NULL;
static int opnumnow = 0;
static struct tabentry *numtable = NULL;
static struct tabentry *nump = NULL;
static int numnumnow = 0;
%}

delim	 [ \t\n]
letter	 [A-Za-z]
digit	 [0-9]

%%

[ \t\n]+		{/**/}
"/*"(\t|\n|.)*"*/" {return BLOCKCOMMENT;}


%%

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


int installNum(){	
	struct tabentry *temp = malloc(sizeof(struct tabentry));
	temp->sequnceid = ++numnumnow;
	temp->lexem = malloc(strlen(yytext)+1);
	strcpy(temp->lexem, yytext);
	if(numtable == NULL){
		numtable = nump = temp;
		numtable->next = NULL;
	}else{
		nump->next = temp;
		nump = temp;
		nump->next = NULL;
	}
	return numnumnow;
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
