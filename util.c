#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void *allocateArray(int rows, int columns) {
	double* arr;
	arr =calloc(sizeOf(double) * (row * columns));
}

int ListInit(List* l, int max_elmt_size){
	List l;
	l->data = collac(max_elmt_size * 10);
	l->max_element_size = max_elmt_size;
	l->max_size = 10;
	l->size = 0;
	return 0;
}

void listAddEnd(List* l, void* elmt){
	if (l->size != l->max_size) {
		l->data + (l->max_element_size * l->size) = *elmt;
	}
}

void* listGet(List* l, int index){

	return nullptr;
}
