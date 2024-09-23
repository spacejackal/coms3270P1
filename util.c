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
		l->data = elmt;
		l->size++;
	}
}

void* listGet(List* l, int index){
	int size = l->size;
	void* p = l->data;
	p += 4;

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
	printf("first thing in list: %d\n", *px);
	printf("------------------------------------------\n");
	int x = 5;
	int* pxx = &x;
	listAddEnd(pLi, pxx);
	px = (int*)listGet(pLi, 0);
	printf("adding 5 to the list\n");
	printf("size of list: %i\n", pLi->size);
	printf("first thing in list: %d\n", *px);

	printf("------------------------------------------\n");
	int y = 2;
	int* py = &y;
	listAddEnd(pLi, py);
	px = (int*)listGet(pLi, 0);
	printf("adding 2 to the list\n");
	printf("size of list: %i\n", pLi->size);
	printf("first thing in list: %d\n", *px);
	px = (int*)listGet(pLi, 1);
	printf("second thing in list: %d\n", *px);

	
	return 1;
}
