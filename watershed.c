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



pPC->wcoef = wcoef;
pPC->ecoef = ecoef;
printf("stats are high %lf, and low %lf\n", pPC->points->stats->high, pPC->points->stats->low);
pcd_t* temp = listGet(pPC->points, 1001);
printf("the temp point are at x %lf, and y %lf and height %lf\n", temp->x, temp->y,temp->height);

initializeWatershed(pPC);
printf("initailized the watershed with no issues\n");
pcd_t* east = temp->east;
printf("the east pointt are at x %lf, and low %lf and height %lf\n", east->x, east->y, east->height);
pcd_t* west = temp->west;
printf("the west pointt are at x %lf, and low %lf and height %lf\n", west->x, west->y, west->height);
pcd_t* north = temp->north;
printf("the north pointt are at x %lf, and low %lf and height %lf\n", north->x, north->y, north->height);
pcd_t* south = temp->south;
printf("the south pointt are at x %lf, and low %lf and height %lf\n", south->x, south->y, south->height);

imagePointCloud(pPC, out);


return 1;

}