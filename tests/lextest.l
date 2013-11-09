%{
#include "tokens.h"
%}

/*regular definitions*/
%%
[ \t\n]		{/* no action and no return*/}
if			{return IF;} 
then		{return THEN;}
else		{return ELSE;}
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
