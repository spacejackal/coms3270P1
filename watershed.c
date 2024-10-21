#include <stdio.h>
#include <string.h>
#include "util.h"
#include "pointcloud.h"

int main(int argc, char* argv[]) {
	char infile = argv[1];
	int iter = atoi(argv[2]);
	float iwater = atof(argv[3]);
	float wcoef = atof(argv[4]);
	float ecoef = atof(argv[5]);
	char ofilebase* = argv[6];
	int seq = atoi(argv[7]);
	
pointcloud_t pc;
pointcloud_t* pPC;
//pPC->wcoef = (double*)wcoef;
//pPC->ecoef = (double*)ecoef;
FILE* pInFile = fopen(infile,r);
pPC = readPointCloudData(pInFile);


	

}