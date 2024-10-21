#include <stdio.h>
#include "util.h"
#include "pointcloud.h"

int main(int argc, char* argv[]) {
	char infile = argv[1];
	int iter = argv[2];
	float iwater = argv[3];
	float wcoef = argv[4];
	float ecoef = argv[5];
	char ofilebase = argv[6];
	int seq = argv[7];
	
pointcloud_t pc;
pointcloud_t* pPC;
//pPC->wcoef = (double*)wcoef;
//pPC->ecoef = (double*)ecoef;
FILE* pInFile = fopen(infile,r);
pPC = readPointCloudData(pInFile);


	

}