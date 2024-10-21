#include <stdio.h>
#include <string.h>
#include "util.h"
#include "pointcloud.h"

int main(int argc, char* argv[]) {
	printf("we got to main 1\n");
	const char* __restrict infile = argv[1];
	printf("we got to main 2\n");
	int iter = atoi(argv[2]);
	printf("we got to main 3\n");
	float iwater = atof(argv[3]);
	printf("we got to main 4\n");
	float wcoef = atof(argv[4]);
	printf("we got to main 5\n");
	float ecoef = atof(argv[5]);
	printf("we got to main 6\n");
	const char* ofilebase = argv[6];
	printf("we got to main 7\n");
	int seq = atoi(argv[7]);
	printf("we are defineing the PC\n");
pointcloud_t pc;
pointcloud_t* pPC;
pPC->wcoef = wcoef;
pPC->ecoef = ecoef;
FILE* pInFile = fopen(infile,"r");
pPC = readPointCloudData(pInFile);


	

}