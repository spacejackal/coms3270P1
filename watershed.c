#include <stdio.h>
#include "util.h"
#include "pointcloud.h"

int main(int argc, char** argv) {
	char* infile;
	int* iter;
	float* iwater;
	float* wcoef;
	float* ecoef;
	char* ofilebase;
	int* seq;
	
sscanf( char* infile,  int* iter,  float* iwater, float* wcoef,  float* ecoef, char* ofilebase, int* seq);
pointcloud_t pc;
pointcloud_t* pPC;
//pPC->wcoef = (double*)wcoef;
//pPC->ecoef = (double*)ecoef;
FILE* pInFile = (FILE*)infile;
pPC = readPointCloudData(pInFile);


	

}