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
	float wcoef;
	float ecoef;

}pointcloud_t;

/*
* function to create an image
*/
void imagePointCloud(pointcloud_t* pc, char* filename);


int initializeWatershed(pointcloud_t* pc);


void watershedAddUniformWater(pointcloud_t* pc, double amount);

void watershedStep(pointcloud_t* pc);

//void watershedStep(pointcloud* pc);

/*
* function to read points and store them
*/
pointcloud_t* readPointCloudData(FILE* stream);

double helper(pointcloud_t* pc, double t1, double w1, double t2, double w2);

void imagePointCloudWater(pointcloud_t* pc, double maxwd, char* filename);


#endif // !POINTCLOUD

