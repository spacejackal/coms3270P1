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
pcd_t* temp = listGet(pPC->points, 2205);

double low = pPC->points->stats->low;

printf("the pc stats are low:%lf and high:%lf pre watershed \n", pPC->points->stats->low, pPC->points->stats->high);

initializeWatershed(pPC);
pcd_t* east = temp->east;
printf("the east pointt are at x %d, and low %d and height %lf\n", east->relitiveX, east->relitiveY, east->height);
pcd_t* west = temp->west;
printf("the west pointt are at x %d, and low %d and height %lf\n", west->relitiveX, west->relitiveY, west->height);
pcd_t* north = temp->north;
printf("the north pointt are at x %d, and low %d and height %lf\n", north->relitiveX, north->relitiveY, north->height);
pcd_t* south = temp->south;
printf("the south pointt are at x %d, and low %d and height %lf\n", south->relitiveX, south->relitiveY, south->height);
char* wor = "wor";

printf("the pc stats are low:%lf and high:%lf \n", pPC->points->stats->low, pPC->points->stats->high);

pPC->points->stats->low = low;

imagePointCloud(pPC, wor);


return 1;

}