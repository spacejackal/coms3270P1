

#ifndef UTIL
#define UTIL
void* allocateArray(int, int);
#define TDOD(row,colom,width) row * width +  colom


typedef struct {
	double high;
	double low;
}Stats;

typedef struct {
	int max_size;
	int max_element_size;
	void* data;
	int size;
	Stats* stats;
} List;

int ListInit(List* l, int max_elmt_size);

void listAddEnd(List* l, void* elmt);

void* listGet(List* l, int index);

#endif // !UTIL

