

#ifndef UTIL
#define UTIL
void* allocateArray(int, int);
#define TDOD(row,colom,width) ((row * width) +  colom)

/*
* Stats is mainly used to keep track of the high point and low point
*/
typedef struct {
	double high;
	double low;
	double minX;
	double minY;
}Stats;

/* 
* List works similerly to ArrayList in java ie, it is a expanding list structue
*/
typedef struct {
	int max_size;
	int max_element_size;
	void* data;
	int size;
	Stats* stats;
} List;

/*
* inichalized a list based on the size of element in the array
*/
int ListInit(List* l, int max_elmt_size);

/*
* added a new element to a list
*/
void listAddEnd(List* l, void* elmt);

/*
* gets the element at an index
*/
void* listGet(List* l, int index);

void listSet(List* l, int index, void* data);

int listInitFull(List* l, int max_elmt_size, int size);

#endif // !UTIL

