#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include <string.h>

/*
* allocates a 2D array of doubles to the spesifications given
*/
void *allocateArray(int rows, int columns) {
	double* arr;
	arr = calloc((rows * columns) , sizeof(double));
	return arr;
}

/*
* inichalizes a list based on the size of each element
*/
int ListInit(List* l, int max_elmt_size){
	l = malloc(sizeof(List));
	l->data = calloc(10, max_elmt_size);
	l->max_element_size = max_elmt_size;
	l->max_size = 10;
	l->size = 0;
	return 0;
}

int listInitFull(List* l, int max_elmt_size, int size) {

	l->data = calloc(size, max_elmt_size);
	l->max_element_size = max_elmt_size;
	l->max_size = size;
	l->size = size;
	return 0;
}

/*
* addes an element to the end of a list
*/
void listAddEnd(List* l, void* elmt){
	if (l->size >= l->max_size) {
		l->data = realloc(l->data, (l->max_size * 2) * l->max_element_size);
		l->max_size = l->max_size * 2;
	}
	memcpy((char*)l->data + (l->size * l->max_element_size), elmt, l->max_element_size);
	l->size++;
}

/*
* gets an element from a list based on index given
*/
void* listGet(List* l, int index){
	
	return (char*)l->data + (index *l->max_element_size);
}

void listSet(List* l, int index, void* emlt) {
	memcpy((char*)l->data + (index * l->max_element_size), emlt, l->max_element_size);
}

