#include <stdio.h>
#include "error.h"

void error(char *errorMessage){
	fprintf(stderr, "ERROR: %s\n", errorMessage);
}
