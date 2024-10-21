#include <stdio.h>
#include "pointcloud.h"
#include "util.h"

int main(int argc, char** argv) {
	char* infile;
	int* iter;
	float* iwater;
	float* wcoef;
	float* ecoef;
	char* ofilebase;
	int* seq;
	
	int sscanf(const char* infile, const int* iter, const float* iwater, const float* wcoef, const float* ecoef, const char* ofilebase, const int* seq);
pointcloud_t pc;
pointcloud_t* pPC;
pPC->wcoef = wcoef;
pPC->ecoef = ecoef;
FILE* pInFile = (FILE*)infile;
pPC = readPointCloudData(pInFile);


	

}