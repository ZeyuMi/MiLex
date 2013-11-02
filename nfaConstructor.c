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


void replace(char *, char *, char *);


/*replace all the definitions in subsequent definitions and regular expressions*/
void replaceAllDef(){
	struct Defentry *dp = definitions;
	while(NULL != dp){
		struct Defentry *deftemp = dp->next;
		while(NULL != deftemp){
			replace(deftemp->definition, dp->name, dp->definition);
			deftemp = deftemp->next;
		}
		/*now replace definition in regular expressions*/
		struct REentry *retemp = regexps;
		while(NULL != retemp){
			replace(retemp->regexp, dp->name, dp->definition);
			retemp = retemp->next;
		}
		dp = dp->next;
	}
}


/*substitute character class with its correspoinding characters*/
void substituteCharClass(){

}

void replace(char *origin, char *rep, char *with){
	char *op = origin;
	int replen = strlen(rep);
	int withlen = strlen(with);
	if(NULL == origin || NULL == rep || NULL == with){
		return;
	}
	int count = 0;
	while(NULL != strstr(op, rep)){
		count++;
		op += replen;
	}

	
	char *oldStr = origin;
	op = oldStr;
	origin = malloc(strlen(origin) + count * (replen - withlen) + 1);
	np = origin;
	char *lastPos = op;
	char *left = NULL;
	for(int i = 0; i < count; i++){
		left = strstr(op, rep);
		strncpy(np, op, left-op);
		np += (left-op);
		op += (left-op);
		strncpy(np, with, withlen);
		np += withlen;
		op += replen;
	}
	strcpy(np,op);
	free(oldStr);
}

int main(){
	char *a;
	strcpy(a, "123412341234");
	replace(a, "123", "aaa");
	printf("%s\n", a);
}
