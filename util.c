#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void *allocateArray(int rows, int columns) {
	double* arr;
	arr = calloc((rows * columns), sizeof(double));
}

int ListInit(List* l, int max_elmt_size){

	l->data = collac(10 , max_elmt_size);
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
