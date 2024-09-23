#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include <string.h>

void *allocateArray(int rows, int columns) {
	double* arr;
	arr = calloc((rows * columns) , sizeof(double));
	return arr;
}

int ListInit(List* l, int max_elmt_size){

	l->data = calloc(10, max_elmt_size);
	printf("the adress of data is: %p ---------", &l->data);
	l->max_element_size = max_elmt_size;
	l->max_size = 10;
	l->size = 0;
	return 0;
}

void listAddEnd(List* l, void* elmt){
	if (l->size >= l->max_size) {
		l->data = realloc(l->data, (l->max_size * 2) * l->max_element_size);
		l->max_size = l->max_size * 2;
	}
	memcpy((char*)l->data + (l->size * l->max_element_size), elmt, l->max_element_size);
	l->size++;
}

void* listGet(List* l, int index){
	
	return (char*)l->data + (index *l->max_element_size);
}

