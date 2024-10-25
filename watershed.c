#include <stdio.h>
#include <string.h>
#include "util.h"
#include "pointcloud.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {
	const char* __restrict infile = argv[1];
	int iter = atoi(argv[2]);
	float iwater = atof(argv[3]);
	float wcoef = atof(argv[4]);
	float ecoef = atof(argv[5]);
	char* ofilebase = argv[6];
	float wdmax = atof(argv[7]);
	int seq = atoi(argv[8]);

pointcloud_t pc;
pointcloud_t* pPC = (pointcloud_t*)malloc(sizeof(pointcloud_t));

FILE* pInFile = fopen(infile,"r");


pPC = readPointCloudData(pInFile);
double twcoef = (double)wcoef;
double tecoef = (double)ecoef;

pPC->wcoef = twcoef;
pPC->ecoef = tecoef;

double low = pPC->points->stats->low;
double high = pPC->points->stats->high;

printf("the pc stats are low:%lf and high:%lf pre watershed \n", pPC->points->stats->low, pPC->points->stats->high);
//imagePointCloudWater(pPC,wdmax, "preOut");

initializeWatershed(pPC);

pPC->points->stats->low = low;
pPC->points->stats->high = high;

watershedAddUniformWater(pPC, iwater);

pcd_t* temp = listGet(pPC->points, 0);

//printf("other info Rx:%lf Ry:%lf col:%d row:%d height:%lf water:%lf \n", temp->x, temp->y, temp->col, temp->row, temp->height,temp->wd);
//imagePointCloudWater(pPC, wdmax, "outWater");
pcd_t* north = temp->north;
pcd_t* east = temp->east;
pcd_t* west = temp->west;
pcd_t* south = temp->south;
//printf("NORTH info Rx:%lf Ry:%lf col:%d row:%d height:%lf \n", north->x, north->y, north->relitiveX, north->relitiveY, north->height);
//printf("SOUTH info Rx:%lf Ry:%lf col:%d row:%d height:%lf \n", south->x, south->y, south->col, south->row, south->height);
//printf("EAST info Rx:%lf Ry:%lf col:%d row:%d height:%lf \n", east->x, east->y, east->col, east->row, east->height);
//printf("WEST info Rx:%lf Ry:%lf col:%d row:%d height:%lf \n", west->x, west->y, west->relitiveX, west->relitiveY, west->height);




watershedStep(pPC);

pPC->points->stats->low = low;
pPC->points->stats->high = high;

//imagePointCloudWater(pPC,wdmax, ofilebase);
int totalCount =0;
int seqCount = 1;
char num[64];
char ofile[64];
for (int i = 0; i < iter; i++) {
	if (seqCount == seq) {
		//sprintf(num, "%d", totalCount);
		strcpy(ofile, ofilebase);
		//strcat(ofile, num);
		strcat(ofile, ".gif");

		imagePointCloudWater(pPC, wdmax, ofilebase);
		seqCount = 0;
		totalCount++;
	}
	//pPC->points->stats->low = low;
	watershedStep(pPC);
	seqCount++;
}


return 1;

}