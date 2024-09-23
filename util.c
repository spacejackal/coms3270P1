#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void *allocateArray(int rows, int columns) {
	double* arr;
	arr = calloc((rows * columns), sizeof(double));
}

int ListInit(List* l, int max_elmt_size){

	l->data = (int*)calloc(10 , max_elmt_size);
	l->max_element_size = max_elmt_size;
	l->max_size = 10;
	l->size = 0;
	return 0;
}

void listAddEnd(List* l, void* elmt){
	if (l->size <= l->max_size) {
		l->data + l->size = elmt;
		l->size += 1;
	}
}

void* listGet(List* l, int index){
	int size = l->size;
	void* p = l->data;
	p += (size* l->max_element_size);

	return p ;
}

int main() {
	List li;
	List* pLi = &li;
	ListInit(pLi, sizeof(int));
	printf("size of list: %i\n", pLi->size);
	printf("max size of list: %i\n", li.max_size);
	printf("max elemnt size: %i\n", pLi->max_element_size);
	int* px = (int*)listGet(pLi, 0);
	printf("first thing in list %d\n", *px);
	int x = 5;
	int* pxx = &x;
	listAddEnd(pLi, px);
	printf("size of list: %i\n", pLi->size);

	
	return 1;
}
