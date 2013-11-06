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
	struct edge *next;
};

int addVertex(int, char *);

int addEdge(int, int, char);

void destroyGraph();

int isVertexExists(int);

int isConnectTo(int, int);

struct vertex *getVertex(int);

int addActionToVertex(int, char *);

void printGraph();
