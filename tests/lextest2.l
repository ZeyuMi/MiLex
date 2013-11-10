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

{delim}+		{/*no action and no return */}
auto			{return AUTO;}
break			{return BREAK;}
case			{return CASE;}
char			{return CHAR;}
const			{return CONST;}
continue		{return CONTINUE;}
default			{return DEFAULT;}
do				{return DO;}
double			{return DOUBLE;}
else			{return ELSE;}
enum			{return ENUM;}
extern			{return EXTERN;}
float			{return FLOAT;}
for				{return FOR;}
goto			{return GOTO;}
if				{return IF;}
int				{return INT;}
long			{return LONG;}
register		{return REGISTER;}
return			{return RETURN;}
short			{return SHORT;}
signed			{return SIGNED;}
sizeof			{return SIZEOF;}
static			{return STATIC;}
struct			{return STRUCT;}
switch			{return SWITCH;}
typedef			{return TYPEDEF;}
union			{return UNION;}
unsigned		{return UNSIGNED;}
void			{return VOID;}
volatile		{return VOLATILE;}
while			{return WHILE;}
_Packed			{return _PACKED;}

({letter}|_)({letter}|{digit}|_)*  {yylval = installID(); return ID;} 
{digit}+(\.{digit}+)?(E[+-]?{digit}+)? {yylval = installNum(); return NUM;}
":"				{return COLON;}
","				{return COMMA;}
";"				{return SEMICOLON;}
"("				{return LEFTPAREN;}
")"				{return RIGHTPAREN;}
"["				{return LEFTBRACKET;}
"]"				{return RIGHTBRACKET;}
"{"				{return LEFTBRACE;}
"}"				{return RIGHTBRACE;}
"="				{yylval = installOP(); return OP;}
"<"				{yylval = installOP(); return OP;}
"<="			{yylval = installOP(); return OP;}
"=="			{yylval = installOP(); return OP;}
"!="			{yylval = installOP(); return OP;}
">"				{yylval = installOP(); return OP;}
">="			{yylval = installOP(); return OP;}
"+"				{yylval = installOP(); return OP;}
"++"			{yylval = installOP(); return OP;}
"-"				{yylval = installOP(); return OP;}
"--"			{yylval = installOP(); return OP;}
"*"				{yylval = installOP(); return OP;}
"/"				{yylval = installOP(); return OP;}
"%"				{yylval = installOP(); return OP;}
">>"			{yylval = installOP(); return OP;}
"<<"			{yylval = installOP(); return OP;}
">"				{yylval = installOP(); return OP;}
"<"				{yylval = installOP(); return OP;}
"&"				{yylval = installOP(); return OP;}
"->"			{yylval = installOP(); return OP;}

"|"				{return BITINCLUOR;}
"&"				{return BITAND;}
"^"				{return BITEXCLUEOR;}
"~"				{return COMPLEMENT;}
"||"			{return LOGICOR;}
"&&"			{return LOGICAND;}
"!"				{return LOGICNOT;}

"?"				{return CONEXPSYMBOL;}

'(.|\\.)'		{return CHARLITERAL;}
\".*\"			{return STRINGLITERAL;}

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
