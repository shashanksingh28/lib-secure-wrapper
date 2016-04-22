#include <stdlib.h>
#include <stdio.h>

int main(){
	int *p1 = malloc(4);
	char *p2 = malloc(1);
	free(p1);
	free(p2);
	char *p3 = malloc(60);
}
