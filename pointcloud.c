#include <stdio.h>
#include "util.h"
#include "util.c"
#include "pointcloud.h"
#include "bmp.h"
#include "bmp.c"


//this struct is used to keep track of points in a condensed and easy manner


//the main method calls stat1
int main() {
	List l;
	List* pL = &l;
	Stats s;
	Stats* pS = &s;
	pL->stats = pS;
	char filename[] = "imagePointCloud.out";

	ListInit(pL, sizeof(pcd_t));
	int width = 0;
	int* pWidth = &width;
	readPointCloudData(stdin, pWidth, pL);
	//stat1();
	printf("the width: %d", width);
	printf("the high point %lf  ", s.high);
	printf("the low point %lf   ", s.low);
	imagePointCloud(pL, width, filename);
	return 1;
}



//stat1() gets the highest and lowest point and also computes the average
int stat1() {
	pcd_t high; //defines the struct to keep track of the high point
	pcd_t low;  //defines the struct to keep track of the low point
	pcd_t temp; //defines the struct to keep a temp point to compare to the high and low points
	double total;	   //defines the total to compute the average
	int count = 1;		//defines a count to keep track of the total number of points assessed
	
	scanf("%lf %lf %lf", &high.x, &high.y, &high.height); //gets the first point and makes it the high point;
	low.x = high.x;		//bellow assinments are used to make the low point the same as the high point
	low.y = high.y;
	low.height = high.height;
	total += high.height;

	while (scanf("%lf %lf %lf", &temp.x, &temp.y, &temp.height) != EOF) { //reads all set of 3  values and adding it to the temp point
		if (temp.height > high.height) {  //if the temp point has more height the the high point, make it the high point
			high.x = temp.x;
			high.y = temp.y;
			high.height = temp.height;
		}
		else if (temp.height < low.height) { //if the temp point has less height then the low point, make it the low point
			low.x = temp.x;
			low.y = temp.y;
			low.height = temp.height;
		}
		count++;	//adds to the number of points assessed
		total += temp.height;  //adds the height of the temp point to the total of find the average
	}
	total /= count;


	printf("High point: x = %.1f, y = %.1f, height = %.15f \n", high.x, high.y, high.height); //prints out the x, y, and height value of the high point
	printf("Low point: x = %.1f, y = %.1f, height = %.15f \n", low.x, low.y, low.height);
	printf("Average %.15f , number of points %d \n", total, count); //prints out the average of the points looked at and the total number of points looked at

	return 0;
}


void imagePointCloud(List* l,int width, char* filename) {
	int* pWidth = &width;
	FILE* file = fopen(filename, "w");
	double min = l->stats->low;
	double max = l->stats->high;
	double diff = max - min;
	pcd_t listTemp;
	pcd_t* pListTemp = &listTemp;
	double temp;
	double* pTemp = &temp;
	unsigned int section;
	int height = l->size / width;
	Bitmap* b = bm_create(width, height);
	int writeRow = 0;
	int writeCol = 0;

	void* arr = allocateArray(height, width);
	for (int i = 0; i < l->size; i++) {
		pListTemp = (pcd_t*)listGet(l, i);
		temp = pListTemp->height;
		temp -= min;
		temp /= diff;
		temp *= 256;
		section = (unsigned int)temp;
		printf("the unsighed int is %d", section);
		
	}
	bm_set_color(b, bm_atoi("white"));
	bm_puts(b, 20, 20, "Hello World");
	bm_save(b, "out.gif");

	


}


void readPointCloudData(FILE* stream, int* rasterWidth, List* pL){
	ListInit(pL, sizeof(pcd_t));
	fscanf(stream, "%d", rasterWidth);
	pcd_t high; 
	pcd_t low;  
	pcd_t temp;
	pcd_t* pTemp = &temp;
	double total;

	fscanf(stream, "%lf %lf %lf", &high.x, &high.y, &high.height); 
	low.x = high.x;		
	low.y = high.y;
	low.height = high.height;
	total += high.height;


	while (fscanf(stream,"%lf %lf %lf", &temp.x, &temp.y, &temp.height) != EOF) { 
		listAddEnd(pL,  pTemp);
		if (temp.height > high.height) {  
			high.x = temp.x;
			high.y = temp.y;
			high.height = temp.height;
		}
		else if (temp.height < low.height) { 
			low.x = temp.x;
			low.y = temp.y;
			low.height = temp.height;
		}	
		total += temp.height;
	}
	printf("High point: x = %.1f, y = %.1f, height = %.15f \n", high.x, high.y, high.height); 
	printf("Low point: x = %.1f, y = %.1f, height = %.15f \n", low.x, low.y, low.height);
	printf("Average %.15ls  \n", rasterWidth);
	
	pL->stats->high = high.height;
	pL->stats->low = low.height;

}
