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
#define COMMA 38
#define SEMICOLON 39
#define DOT 40
#define LEFTPAREN 41
#define RIGHTPAREN 42
#define LEFTBRACKET 43
#define RIGHTBRACKET 44
#define LEFTBRACE 45
#define RIGHTBRACE 46
#define CHARLITERAL 47
#define STRINGLITERAL 48



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
