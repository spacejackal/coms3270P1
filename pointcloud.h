#ifndef POINTCLOUD
#define POINTCLOUD
int stat1();

typedef struct pcd_t{		//this struct is used to keep track of points in a condensed and easyilly manage
	double height, x, y , wd;
	void* north;
	void* south;
	void* east;
	void* west;
	int relitiveX;
	int relitiveY;
}pcd_t;

typedef struct {
	List* points;
	int rows;
	int cols;
	double wcoef;
	double ecoef;

}pointcloud_t;

/*
* function to create an image
*/
void imagePointCloud(List* l,int width, char* filename);


int initializeWatershed(pointcloud_t* pc);


void watershedAddUniformWater(pointcloud_t* pc, double amount);


//void watershedStep(pointcloud* pc);

/*
* function to read points and store them
*/
void readPointCloudData(FILE* stream,int* rasterWidth, List* pc);

void imagePointCloudWater(pointcloud_t* pc, double maxwd, char* filename);


#endif // !POINTCLOUD

