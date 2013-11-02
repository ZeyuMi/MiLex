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

extern char *declarations;
extern struct Defentry *definitions;
extern struct REentry *regexps;
extern char *additionalfuncs;
