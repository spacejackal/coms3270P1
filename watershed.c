#include <stdio.h>
#include <string.h>
#include "util.h"
#include "pointcloud.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {
	// the below block of code reads the arguments that are given to watershed when it is run
	const char* __restrict infile = argv[1];
	int iter = atoi(argv[2]);
	float iwater = atof(argv[3]);
	float wcoef = atof(argv[4]);
	float ecoef = atof(argv[5]);
	char* ofilebase = argv[6];
	float wdmax = atof(argv[7]);
	int seq = atoi(argv[8]);

	//inishilizeing the point cloud that will be used
	pointcloud_t pc;
	pointcloud_t* pPC = (pointcloud_t*)malloc(sizeof(pointcloud_t));
	
	//opening the file so it is ready to read
	FILE* pInFile = fopen(infile,"r");
	
	//reading the points from the file expeced and throwing in the wcoef and ecoef to the pointcloud
	pPC = readPointCloudData(pInFile);
	double twcoef = (double)wcoef;
	double tecoef = (double)ecoef;
	pPC->wcoef = twcoef;
	pPC->ecoef = tecoef;
	
	//setting a local high and low as with repeaded calls to imagepointcloud these get lost and become 0
	double low = pPC->points->stats->low;
	double high = pPC->points->stats->high;
	
	//adding the points adjasit to each point
	initializeWatershed(pPC);
	
	//reinitilizeing the high and low
	pPC->points->stats->low = low;
	pPC->points->stats->high = high;
	
	//adding water to each point
	watershedAddUniformWater(pPC, iwater);
	
	//simulateing water based one step of time
	watershedStep(pPC);
	
	
	pPC->points->stats->low = low;
	pPC->points->stats->high = high;
	
	//getting for loop ready so .gif images are made correctly
	int totalCount =0;
	int seqCount = 1;
	char num[64];
	char ofile[64];

	//using a loop so based on the number inputs creates the correct amout of .gif images
	for (int i = 0; i < iter; i++) {
		if (i % seq == 0) {
			//the below code is computeing the correct name for the out file
			sprintf(num, "%d", i);
			strcpy(ofile, ofilebase);
			strcat(ofile, num);
			strcat(ofile, ".gif");
			pPC->points->stats->low = low;
			pPC->points->stats->high = high;
			
	
			imagePointCloudWater(pPC, wdmax, ofile);
			seqCount = 0;
			totalCount++;
		}
		watershedStep(pPC);
		seqCount++;
	}
	
	
	return 1;

}