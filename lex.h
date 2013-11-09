struct Defentry{
	char *name;
	char *definition;
	struct Defentry *next;
};

struct REentry{
	char *regexp;
	char *action;
	struct REentry *next;
};

struct Funcentry{
	char *body;
	struct Funcentry *next;
};

extern char *declarations;
extern struct Defentry *definitions;
extern struct REentry *regexps;
extern struct Funcentry *additionalfuncs;
extern char *charset;
extern char *program;

#define CONSYMBOL -2
#define NEWLINE 128
#define TAB 129
#define RETURN 130
