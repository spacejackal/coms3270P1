#include <stdio.h>
#include <string.h>
#include "util.h"
#include "pointcloud.h"

int main(int argc, char* argv[]) {
	const char* __restrict infile = argv[1];
	int iter = atoi(argv[2]);
	float iwater = atof(argv[3]);
	float wcoef = atof(argv[4]);
	float ecoef = atof(argv[5]);
	const char* ofilebase = argv[6];

	int seq = atoi(argv[7]);

pointcloud_t pc;
pointcloud_t* pPC;
FILE* pInFile = fopen(infile,"r");


pPC = readPointCloudData(pInFile);
printf("read all the points\n");


pPC->wcoef = wcoef;
pPC->ecoef = ecoef;
printf("stats are high %lf, and low %lf\n", pPC->points->stats->high, pPC->points->stats->low);
pcd_t* temp = listGet(pPC->points, 50);
printf("the temp points are at x %lf, and low %lf and height %lf\n", temp->x, temp->y,temp->height);

initializeWatershed(pPC);

return 1;

}