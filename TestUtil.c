#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "util.c"

int main() {
	List li;
	List* pLi;
	ListInit(pLi, 5);
	printf("size of list: %i", pLi->size);
	printf("max size of list: %i", li.max_size);
	return 1;
}