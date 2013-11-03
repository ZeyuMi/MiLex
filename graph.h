#define EPSILON -1

struct vertex{
	int state;
	char *action;
	struct edge *edges;
	struct vertex *next;
};

struct edge{
	struct vertex *connectsTo;
	char symbol;
};

int addVertex(int, char, char *);

int addEdge(int, int, char);
