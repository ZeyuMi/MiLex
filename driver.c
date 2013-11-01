#include <stdio.h>
#include <string.h>
#include"token.h"
#include"mem.h"

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
				outputfilename = alloc(strlen(*++argv)+1);
				strcpy(outputfilename, *argv);
			}else{
				*(inputfilenames+inputnum) = alloc(strlen(param)+1);
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
				while((tokenname=getToken()) != EOF)
					fprintf(outputfile,"%d : %s\n", tokenname, yytext);
				unsetIn();
				fclose(file);
				afree(filename);
				i++;
		}
		afree(outputfilename);
		fclose(outputfile);
	}
	return 0;
}
