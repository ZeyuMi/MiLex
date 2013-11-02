#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lex.h"
#include "nfaConstructor.h"

void preprocess();

void constructNFA(){
	preprocess();	

}

void replaceAllDef();
void substituteCharClass();


void preprocess(){
	replaceAllDef();
	substituteCharClass();
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


/*substitute character class with its correspoinding characters*/
void substituteCharClass(){

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
