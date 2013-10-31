#include <stdio.h>
#include"token.h"

int main(){
	int tokenname;
	FILE *file = fopen("driver.c", "r");
	setIn(file);
	while((tokenname=getToken()) != EOF)
		printf("%d : %s\n", tokenname, token);
	unsetIn();
	fclose(file);
	return 0;
}
