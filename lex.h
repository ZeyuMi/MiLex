
struct Defentry{
	char *name;
	char *definition;
}

struct REentry{
	char *regexp;
	char *action;
};


extern char *copiedline1;
extern struct Defentry **definitions;
extern struct REentry **regexps;
extern char *copiedline2;
