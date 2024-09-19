#ifndef POINTCLOUD
#define POINTCLOUD
int stat1();
int main();

typedef struct pcd_t{		//this struct is used to keep track of points in a condensed and easy manner
	double height, x, y;
	double *north;
	double *south;
	double *east;
	double *west;};

#endif // !POINTCLOUD

