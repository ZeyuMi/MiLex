%{
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "token.h"
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



%%


