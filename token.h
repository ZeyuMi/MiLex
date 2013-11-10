#define ID 1
#define NUM 2
#define OP 3
#define ASSIGN 4
#define AUTO 5
#define BREAK 6
#define CASE 7
#define CHAR 8
#define CONST 9
#define	CONTINUE 10
#define DEFAULT 11
#define	DO 12
#define	DOUBLE 13
#define	ELSE 14
#define	ENUM 15
#define	EXTERN 16
#define	FLOAT 17
#define	FOR 18
#define	GOTO 19
#define	IF 20
#define	INT 21
#define	LONG 22
#define	REGISTER 23
#define	RETURN 24
#define	SHORT 25
#define	SIGNED 26
#define	SIZEOF 27
#define	STATIC 28
#define	STRUCT 29
#define	SWITCH 30
#define	TYPEDEF 31
#define	UNION 32
#define	UNSIGNED 33
#define	VOID 34
#define	VOLATILE 35
#define	WHILE 36
#define	_PACKED 37
#define COLON 38
#define COMMA 39
#define SEMICOLON 40
#define DOT 41
#define LEFTPAREN 42
#define RIGHTPAREN 43
#define LEFTBRACKET 44
#define RIGHTBRACKET 45
#define LEFTBRACE 46
#define RIGHTBRACE 47
#define CHARLITERAL 48
#define STRINGLITERAL 49

#define BITINCLUOR 50
#define BITAND 51
#define BITEXCLUEOR 52
#define COMPLEMENT 53
#define LOGICOR 54
#define LOGICAND 55
#define LOGICNOT 56

#define CONEXPSYMBOL 57
#define CHARLITERAL 58
#define STRINGLITERAL 59

struct tabentry{
	int sequnceid;
	char *lexem;
	struct tabentry *next;
};


void setIn(FILE *);
void unsetIn();
int getToken();

extern int yyleng;
extern char yytext[];
extern int yylval;
