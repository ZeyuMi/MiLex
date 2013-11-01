#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"token.h"

int main(int argc, char *argv[]){
	char *outputfilename = NULL;
	char *inputfilenames[10];
	int inputnum = 0;
	if(argc == 1){
		fprintf(stderr, "ERROR: not enough parameters\n");
	}else{
		while(--argc > 0){
			char *param = *++argv;
			if(strcmp(param, "-o") == 0){
				argc--;
				outputfilename = malloc(strlen(*++argv)+1);
				strcpy(outputfilename, *argv);
			}else{
				*(inputfilenames+inputnum) = malloc(strlen(param)+1);
				strcpy(*(inputfilenames+inputnum), param);
				inputnum++;
			}
		}
		FILE *outputfile = NULL;
		if(outputfilename == NULL)
			outputfile = stdout;
		else
			outputfile = fopen(outputfilename, "w");
		int i = 0;
		while(i < inputnum){
				char *filename = *(inputfilenames + i);
				FILE *file = fopen(filename, "r");
				int tokenname;
				fprintf(outputfile, "file %s\n", filename);
				setIn(file);
				while((tokenname=getToken()) != EOF){
					switch(tokenname){
						case OP:
						case ID:
							fprintf(outputfile, "<%d,%s,%d>\n", tokenname, yytext, yylval);
							break;
						case ASSIGN:
						case NUMBER:
							fprintf(outputfile, "<%d,%s>\n", tokenname, yytext);
							break;
						default:
							;
					}
				}
				unsetIn();
				fclose(file);
				free(filename);
				i++;
		}
		free(outputfilename);
		fclose(outputfile);
	}
	return 0;
}
