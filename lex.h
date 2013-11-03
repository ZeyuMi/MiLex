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

#define CONSYMBOL -2
