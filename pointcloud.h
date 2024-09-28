#ifndef POINTCLOUD
#define POINTCLOUD
int stat1();
int main();


typedef struct pcd_t{		//this struct is used to keep track of points in a condensed and easy manner
	double height, x, y , water_level;
	pcd_t* north;
	pcd_t* south;
	pcd_t* east;
	pcd_t* west;
}pcd_t;

void imagePointCloud(List* l,int width, char* filename);

void readPointCloudData(FILE* stream,int* rasterWidth, List* pc);
#endif // !POINTCLOUD

