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
	const char* ofilebase = argv[6];
	float wdmax = atof(argv[7])
	int seq = atoi(argv[8]);

pointcloud_t pc;
pointcloud_t* pPC = (pointcloud_t*)malloc(sizeof(pointcloud_t));
FILE* pInFile = fopen(infile,"r");


pPC = readPointCloudData(pInFile);
pPC->wcoef = wcoef;
pPC->ecoef = ecoef;

double low = pPC->points->stats->low;

printf("the pc stats are low:%lf and high:%lf pre watershed \n", pPC->points->stats->low, pPC->points->stats->high);

initializeWatershed(pPC);

pPC->points->stats->low = low;

watershedAddUniformWater(pPC, iwater);

watershedStep(pPC);

pPC->points->stats->low = low;
imagePointCloudWater(pPC,wdmax, ofilebase);
int totalCount =0;
int seqCount = 0;
for (int i = 0; i < iter; i++) {
	if (seqCount == seq) {
		char ofile[20];
		strcpy(ofile, ofilebase);
		strcat(ofile, (itoa(totalCount)))
		imagePointCouldWater(pPC, wdmax, ofilebase);
		seqCount = 0;
		totalCount++;
	}
	pPC->points->stats->low = low;
	watershedStep(pPC);
	seqCount++;
}


return 1;

}