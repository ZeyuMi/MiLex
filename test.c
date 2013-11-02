#include <stdio.h>
#include <string.h>

int main(){
	char *p = "123";
	char *a = p+1;
	printf("%d\n",strstr(a,"") - p);
}
