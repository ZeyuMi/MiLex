enum states{STATE0 = 1,    //sasdda		aad
			STATE1,
			STATE2,
			STATE3,
			STATE4,
			STATE5,
			STATE6,
			STATE7,
			STATE8,
			STATE9,
			STATE10,
			STATE11,
			STATE12,
			};

/*t
		assadest*/

FILE *in = NULL;

int readDeclareSec();
int readRESec();
int readFuncSec();

int readFile(FILE *file){
	if(file == NULL)
		return -1;
	in = file;
	if(ERROR == readDeclareSec())
		return -1;
	if(ERROR == readRESec())
		return -1;
	if(ERROR == readFuncSec())
		return -1;
	return 1;
}


int getch();
void ungetch(int );
void insertDefEntry(char *);
void insertDefContent(char *);
void insertREEntry(char *);
void insertREAction(char *);
void insertFuncEntry(char *);


struct Defentry *defp = NULL;
int readDeclareSec(){
	int bufferid = initializeCharBuffer();
	int state = STATE0;
	while(1){
		int c = getch();
		if(c == EOF)
			return ERROR;
		switch(state){
			case STATE0:
				if( == c){
					state = STATE1;
				}else if( == c){
					state = STATE9;
				}else if( == c){
					state = STATE0;
				}else{
					state = STATE5;
					addCharElement(bufferid, c);
				}
				break;
			case STATE1:
				if( == c){
					state = STATE2;
				}else if( == c){
					state = STATE4;
				}else if( == c){
					error();
				}else{
					state = STATE5;
					addCharElement(bufferid, c);
				}
				break;
			case STATE2:
				if( == c){
					state = STATE3;
				}else{
					state = STATE2;
				}
				break;
			case STATE3:
				if( == c){
					state = STATE3;
				}else if( == c){
					state = STATE0;
				}else{
					state = STATE2;
				}
				break;
			case STATE4:
				if( == c){
					state = STATE0;
				}else{
					state = STATE4;
				}
				break;
			case STATE5:
				if( == c){
					state = STATE6;
					addCharElement(bufferid, );
					insertDefEntry(getCharBuffer(bufferid));
					rewindCharPointer(bufferid);
				}else if( == c){
					error();
				}else{
					state = STATE5;
					addCharElement(bufferid, c);
				}
				break;
			case STATE6:
				if( == c){
					state = STATE6;
				}else if( == c){
					error();
				}else{
					state = STATE7;
					ungetch(c);
				}
				break;
			case STATE7:
				if( == c){
					state = STATE0;
					addCharElement(bufferid, );
					insertDefContent(getCharBuffer(bufferid));
					rewindCharPointer(bufferid);
				}else if( == c){
					state = STATE8;
					addCharElement(bufferid, c);
				}else{
					state = STATE7;
					addCharElement(bufferid, c);
				}
				break;
			case STATE8:
				if( == c){
					state = STATE7;
					addCharElement(bufferid, c);
				}else if( == c){
					error();
				}else{
					state = STATE8;
					addCharElement(bufferid, c);
				}
				break;
			case STATE9:
				if( == c){
					state = STATE10;
				}else if( == c){
					state = STATE0;
					destroyCharBuffer(bufferid);
					return 1;
				}else{
					error();
				}
				break;
			case STATE10:
				if( == c){
					state = STATE11;
				}else{
					state = STATE10;
					addCharElement(bufferid, c);
				}
				break;
			case STATE11:
				if( == c){
					state = STATE0;
				    declarations = malloc(charSize(bufferid));
					strcpy(declarations, getCharBuffer(bufferid));
					rewindCharPointer(bufferid);
				}else{
					error();
				}
				break;
			default:
				error();
		}
	}
}

struct REentry *rep = NULL;
int readRESec(){
	int bufferid = initializeCharBuffer();
	int state = STATE0;
	while(1){
		char c = getch();
		if(c == EOF)
			return ERROR;
		switch(state){
			case STATE0:
				if( == c){
					state = STATE1;
				}else if( == c){
					state = STATE10;
				}else if( == c){
					state = STATE0;
				}else{
					state = STATE5;
					ungetch(c);
				}
				break;
			case STATE1:
				if( == c){
					state = STATE2;
				}else if( == c){
					state = STATE4;
				}else if( == c){
					error();
				}else{
					state = STATE5;
					ungetch(c);
				}
				break;
			case STATE2:
				if( == c){
					state = STATE3;
				}else{
					state = STATE2;
				}
				break;
			case STATE3:
				if( == c){
					state = STATE3;
				}else if( == c){
					state = STATE0;
				}else{
					state = STATE2;
				}
				break;
			case STATE4:
				if( == c){
					state = STATE0;
				}else{
					state = STATE4;
				}
				break;
			case STATE5:
				if( == c){
					state = STATE8;
					addCharElement(bufferid, );
					insertREEntry(getCharBuffer(bufferid));
					rewindCharPointer(bufferid);
				}else if( == c){
					error();
				}else if( == c){
					state = STATE6;
					addCharElement(bufferid,c);
				}else if( == c){
					state = STATE7;
					addCharElement(bufferid, c);
				}else{
					state = STATE5;
					addCharElement(bufferid,c);
				}
				break;
		
			case STATE6:
				if( == c){
					state = STATE5;
					addCharElement(bufferid,c);
				}else if( == c){
					error();
				}else{
					state = STATE6;
					addCharElement(bufferid,c);
				}
				break;
			case STATE7:
				if( == c){
					state = STATE5;
					addCharElement(bufferid,c);
				}else if( == c){
					error();
				}else{
					state = STATE7;
					addCharElement(bufferid,c);
				}
				break;
			case STATE8:
				if( == c){
					state = STATE8;
				}else if( == c){
					state = STATE9;
				}else{
					error();
				}
				break;
			case STATE9:
				if( == c){
					state = STATE0;
					addCharElement(bufferid, );
					insertREAction(getCharBuffer(bufferid));
					rewindCharPointer(bufferid);
				}else{
					state = STATE9;
					addCharElement(bufferid,c);
				}
				break;
			case STATE10:
				if( == c){
					state = STATE0;
					destroyCharBuffer(bufferid);
					return 1;
				}
				break;
			defualt:
				error();
		}
	}
}

struct Funcentry *funcp = NULL;
int readFuncSec(){
	int leftBraceNum = 0;
	int bufferid = initializeCharBuffer();
	int state = STATE0;
	while(1){
		char c = getch();
		if(c == EOF){
			if(state != STATE0)
				return ERROR;
			else{
				destroyCharBuffer(bufferid);
				return 1;
			}
		}
		switch(state){
			case STATE0:
				if( == c){
					state = STATE1;
				}else if(isalpha(c) ||  == c){
					state = STATE5;
					leftBraceNum = 0;
					addCharElement(bufferid,c);
				}else if( == c){
					state = STATE0;
				}else{
					error();
				}
				break;
			case STATE1:
				if( == c){
					state = STATE2;
				}else if( == c){
					state = STATE4;
				}else{
					error();
				}
				break;
			case STATE2:
				if( == c){
					state = STATE3;
				}else{
					state = STATE2;
				}
				break;
			case STATE3:
				if( == c){
					state = STATE3;
				}else if( == c){
					state = STATE0;
				}else{
					state = STATE2;
				}
				break;
			case STATE4:
				if( == c){
					state = STATE0;
				}else{
					state = STATE4;
				}
				break;
			case STATE5:
				if( == c){
					state = STATE6;
					addCharElement(bufferid,c);
				}else if( == c){
					state = STATE5;
					leftBraceNum++;
					addCharElement(bufferid,c);
				}else if( == c){
					state = STATE7;
					addCharElement(bufferid,c);
				}else if(c == ){
					leftBraceNum--;
					addCharElement(bufferid,c);
					if(0 == leftBraceNum){
						state = STATE0;
						addCharElement(bufferid, );
						insertFuncEntry(getCharBuffer(bufferid));
						rewindCharPointer(bufferid);
					}else{
						state = STATE5;
					}
				}else{
					state = STATE5;
					addCharElement(bufferid,c);
				}
				break;
			case STATE6:
				addCharElement(bufferid,c);
				if( == c){
					state = STATE5;
				}else if( == c){
					error();
				}else{
					state = STATE6;
				}
				break;
			case STATE7:
				addCharElement(bufferid,c);
				if( == c){
					state = STATE8;
				}else if( == c){
					state = STATE10;
				}else{
					error();
				}
				break;
			case STATE8:
				addCharElement(bufferid,c);
				if( == c){
					state = STATE9;
				}else{
					state = STATE8;
				}
				break;
			case STATE9:
				addCharElement(bufferid,c);
				if( == c){
					state = STATE9;
				}else if( == c){
					state = STATE5;
				}else{
					state = STATE8;
				}
				break;
			case STATE10:
				addCharElement(bufferid,c);
				if( == c){
					state = STATE5;
				}else{
					state = STATE10;
				}
				break;
			default:
				error();
		}
	}
}


void insertDefEntry(char *name){
	struct Defentry *temp = malloc(sizeof(struct Defentry));
	if(NULL == definitions){
		definitions = defp = temp;			
	}else{
		defp->next = temp;
		defp = temp;
	}
	temp->name = malloc(strlen(name)+1);
	strcpy(temp->name, name);
	temp->definition = NULL;
	temp->next = NULL;
}


void insertDefContent(char *def){
	defp->definition = malloc(strlen(def)+1);
	strcpy(defp->definition, def);
}


void insertREEntry(char *re){
	struct REentry *temp = malloc(sizeof(struct REentry));
	if(NULL == regexps){
		regexps = rep = temp;			
	}else{
		rep->next = temp;
		rep = temp;
	}
	temp->regexp = malloc(strlen(re)+1);
	strcpy(temp->regexp, re);
	temp->action = NULL;
	temp->next = NULL;
}


void insertREAction(char *action){
	rep->action = malloc(strlen(action)+1);
	strcpy(rep->action, action);
}


void insertFuncEntry(char *body){
	struct Funcentry *temp = malloc(sizeof(struct Funcentry));
	if(NULL == additionalfuncs){
		additionalfuncs = funcp = temp;			
	}else{
		funcp->next = temp;
		funcp = temp;
	}
	temp->body = malloc(strlen(body)+1);
	strcpy(temp->body, body);
	temp->next = NULL;
}



char buf[BUFSIZE];
int bufp = 0;

int getch(){
	return (bufp > 0) ? buf[bufp--] : getc(in);
}


void ungetch(int c){
	if(bufp >= BUFSIZE-1)
		printf();
	else
		buf[++bufp] = c;
}
