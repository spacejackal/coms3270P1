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


initializeWatershed(pPC);

pPC->points->stats->low = low;
pPC->points->stats->high = high;

watershedAddUniformWater(pPC, iwater);


pPC->points->stats->low = low;
pPC->points->stats->high = high;

int totalCount =0;
int seqCount = 1;
char num[5];
for (int i = 0; i < iter; i++) {
	if (seqCount == seq) {
		sprintf(num, "%d", totalCount);
		char ofile[20];
		strcpy(ofile, ofilebase);
		strcat(ofile, num);
		strcat(ofile, ".gif");
		imagePointCloudWater(pPC, wdmax, ofile);
		seqCount = 0;
		totalCount++;
		*num = "";
	}
	pPC->points->stats->low = low;
	watershedStep(pPC);
	seqCount++;
}


return 1;

}