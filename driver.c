#include <stdio.h>
#include"token.h"

int main(){
	int tokenname;
	while((tokenname=getToken()) != EOF)
		printf("%d : %s\n", tokenname, token);
	return 0;
}
