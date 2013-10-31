#include <stdio.h>
#include <string.h>
#include"token.h"

int main(int argc, char *argv[]){
	if(argc == 1){
		fprintf(stderr, "ERROR: not enough parameters\n");
	}else{
		FILE *outputfile = stdout;
		while(--argc > 0){
			char *param = *++argv;
			if(strcmp(param, "-o") == 0){
				argc--;
				outputfile = fopen(*++argv, "w");
			}else{
				char *filename = param;
				fprintf(outputfile, "file %s\n", filename);
				int tokenname;
				FILE *file = fopen(filename, "r");
				setIn(file);
				while((tokenname=getToken()) != EOF)
					fprintf(outputfile,"%d : %s\n", tokenname, token);
				unsetIn();
				fclose(file);
			}
		}
		fclose(outputfile);
	}
	return 0;
}
