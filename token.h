#define ID 1
#define NUMBER 2
#define OP 3
#define ASSIGN 4
#define TOKENSIZE 100

struct identry{
	int sequnceid;
	char *lexem;
};

struct opentry{
	int sequnceid;
	char *lexem;
};

void setIn(FILE *);
void unsetIn();
int getToken();

extern int yyleng;
extern char yytext[TOKENSIZE];
extern int yylval;
