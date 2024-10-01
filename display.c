#include <stdio.h>
#include "util.h"
#include "pointcloud.h"
#include "util.c"
#include "pointcloud.c"
#include "bmp.h"


int main() {
	List l;
	List* pL = &l;
	Stats s;
	Stats* pS = &s;
	pL->stats = pS;
	char filename[] = "out.gif";
	ListInit(pL, sizeof(pcd_t));
	int width = 0;
	int* pWidth = &width;
	readPointCloudData(stdin, pWidth, pL);
	imagePointCloud(pL, width, filename);
	return 1;
}