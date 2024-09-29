#include <stdio.h>
#include "util.h"
#include "util.c"
#include "pointcloud.h"
#include "pointcloud.c"

int main() {
	List l;
	List* pL = &l;
	Stats s;
	Stats* pS = &s;
	pL->stats = pS;
	ListInit(pl, sizeof(pcd_t));
	int width = 0;
	int* pWidth = &width;
	readPointCloudData(stdin, pWidth, pL);
	//stat1();
	printf("the width: %d", width);
	printf("the high point %lf  ", s.high);
	printf("the low point %lf   ", s.low);
	return 1;
}