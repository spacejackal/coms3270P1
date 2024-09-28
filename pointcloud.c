#include <stdio.h>
#include "util.h"
#include "util.c"
#include "pointcloud.h"


//this struct is used to keep track of points in a condensed and easy manner


//the main method calls stat1
int main() {
	List l;
	List* pL = &l;
	ListInit(pl, sizeof(pcd_t));
	int width = 0;
	int* pWidth = &width;
	readPointCloudData(stdin, pWidth, pL);
	//stat1();
	printf("the width: %d", width);
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
	double high;
	double low;
	double* pHigh = &high;
	double* pLow = &low;

	FILE* file = fopen(filename, "r");
	readPointCloudData(file, pWidth, l);
	int height = l->size / width;
	void* arr = allocateArray(height, width);
	getHighLow(l,pHigh, pLow);
	
}

/*
* getHighLow takes a list and two pointers, one for low and one for high
* this function then looks at the list to find if any point that was is that list that is either higher or lower
* this continues untill it goes through alll the points to find the highest and lowest points
*/
void getHighLow(List* l,double* high, double* low) { 
	pcd_t temp = listGet(l, 0);
	high = temp->height;
	low = high;
	
	for (int i = 1; i < l->size; i++) {
		temp = listGet(l, i);
		if (temp.height > high) {
			high = temp.height;
		}
		else if (temp.height < low) {
			low = temp.height;
		}
	}
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
	printf("Average %.15f  \n", rasterWidth); 
}
