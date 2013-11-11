struct dfaTTEntry{
	int state;
	int *trans;
	char *action;
	struct dfaTTEntry *next;
};

void addDFANewState(int, char *);
void addDFATransTableEntry(int, int, char);
void printDFATransTable();
void destroyDFATransTable();
struct dfaTTEntry *getTable();
int getTableEntryNum();
