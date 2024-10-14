#ifndef POINTCLOUD
#define POINTCLOUD
int stat1();

typedef struct pcd_t{		//this struct is used to keep track of points in a condensed and easyilly manage
	double height, x, y , wd;
	void* north;
	void* south;
	void* east;
	void* west;
}pcd_t;

/*
* function to create an image
*/
void imagePointCloud(List* l,int width, char* filename);


/*
* function to read points and store them
*/
void readPointCloudData(FILE* stream,int* rasterWidth, List* pc);
#endif // !POINTCLOUD

