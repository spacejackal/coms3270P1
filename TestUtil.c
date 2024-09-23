#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "util.h"

int main() {
	List li;
	List* pLi;
	ListInit(pLi, 5);
	printf("size of list: %l", li.size);
	printf("max size of list: %l", li.max_size);
	return 1;
}