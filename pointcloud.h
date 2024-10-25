#ifndef POINTCLOUD
#define POINTCLOUD
int stat1();

typedef struct pcd_t{		//this struct is used to keep track of points in a condensed and easyilly manage
	double height, x, y , wd;
	void* north;
	void* south;
	void* east;
	void* west;
	int row;
	int col;
}pcd_t;

/*
* the pointcloud_t struct is used to keep track of the points as well as the rows and cols
* also keeps track of wcoef and ecoef so it can used in some functions
*/
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
void imagePointCloud(pointcloud_t* pc, char* filename);

/*
* used so each points knows it's naighbors
*/
int initializeWatershed(pointcloud_t* pc);

/*
* used to add the same amount of water to each point
*/
void watershedAddUniformWater(pointcloud_t* pc, float amount);

/*
* used to compute the change in water for a set of time
* that change of water is then added to the current water at each point
*/
void watershedStep(pointcloud_t* pc);


/*
* function to read points and store them
*/
pointcloud_t* readPointCloudData(FILE* stream);

/*
* used by watershedStep to keep the code easily readable
*/
double helper(double wecof, double t1, double w1, double t2, double w2);

/*
* used to ceate an image shaded blue based on how deep the water is at each point
*/
void imagePointCloudWater(pointcloud_t* pc, double maxwd, char* filename);


#endif // !POINTCLOUD

