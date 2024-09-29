#include <stdio.h>
#include "util.h"
#include "util.c"
#include "pointcloud.h"
#include "pointcloud.c"

int main() {
	List l;
	List* pL = &l;
	ListInit(pl, sizeof(pcd_t));
	int width = 0;
	int* pWidth = &width;
	readPointCloudData(stdin, pWidth, pL);
	//stat1();
	printf("the width: %d", width);
	return 1;
}