%{
#include "tokens.h"
%}

/*regular definitions*/
delim	[ \t\n]
ws		{delim}+
letter	[A-Za-z]
digit	[0-9]
id		{letter}({letter}|{digit})*
number	{digit}+(\.{digit}+)?(E[+-]?{digit}+)?

%%

{ws}		{/* no action and no return*/}
if			{return IF;} 
then		{return THEN;}
else		{return ELSE;}
{id}		{yylval = installID(); return ID;}
{number}	{yylval = installNum(); return NUMBER;}
"<"			{yylval = LT; return RELOP;}
"<="		{yylval = LE; return RELOP;}
"=="		{yylval = EQ; return RELOP;}
"!="		{yylval = NE; return RELOP;}
">"			{yylval = GT; return RELOP;}
">="		{yylval = GE; return RELOP;}

%%

int installID(){
	/*function to install the id

	*/
}

int installNum(){
	/*function to install the num

	*/
}
