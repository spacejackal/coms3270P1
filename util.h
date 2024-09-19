

#ifndef UTIL
#define UTIL
void* allocateArray(int, int);

typedef struct {
	int max_size;
	int max_element_size;
	void* data;
	int size;
} List;

int ListInit(List* l, int max_elmt_size);

void listAddEnd(List* l, void* elmt);

void* listGet(List* l, int index);

#endif // !UTIL

