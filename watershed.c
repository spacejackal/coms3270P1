#include <stdio.h>
#include <string.h>
#include "util.h"
#include "pointcloud.h"

int main(int argc, char* argv[]) {
	printf("we got to main\n");
	const char* __restrict infile = argv[1];
	int iter = atoi(argv[2]);
	float iwater = atof(argv[3]);
	float wcoef = atof(argv[4]);
	float ecoef = atof(argv[5]);
	const char* ofilebase = argv[6];
	int seq = atoi(argv[7]);
	printf("we are defineing the PC\n");
pointcloud_t pc;
pointcloud_t* pPC;
pPC->wcoef = wcoef;
pPC->ecoef = ecoef;
FILE* pInFile = fopen(infile,"r");
pPC = readPointCloudData(pInFile);


	

}