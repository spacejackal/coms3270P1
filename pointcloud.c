#include <stdio.h>
#include "util.h"
#include "pointcloud.h"
#include "bmp.h"




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
	printf("Average %.15f ,\n number of points %d \n", total, count); //prints out the average of the points looked at and the total number of points looked at

	return 0;
}

/*
* this function takes a list of pcd_t after it has already been read
* the height of each point is then calulated and a color value is caludated based on the lowest and highest point
* from there it then paints an image pixel by pixel
* lastly it savees the image to "out.gif"
*/
void imagePointCloud(List* l,int width, char* filename) {
	FILE* file = fopen(filename, "w");
	double min = l->stats->low;
	double max = l->stats->high;
	double diff = max - min;
	pcd_t listTemp;
	pcd_t* pListTemp = &listTemp;
	double temp;
	unsigned int section;
	int height = (l->size / width)+1;
	Bitmap* b = bm_create(width, height);
	int writeRow = 0;
	int writeCol = 0;

	for (int i = 0; i < l->size; i++) {
		pListTemp = (pcd_t*)listGet(l, i);
		temp = pListTemp->height;
		temp -= min;
		temp /= diff;
		temp *= 256;

		section = (unsigned int)temp;
		section += ((unsigned int)temp << 24);
		section += ((unsigned int)temp << 16);
		section += ((unsigned int)temp << 8);

		bm_set_color(b, section);
		bm_putpixel(b, pListTemp->relitiveX, pListTemp->relitiveY);

		/*if (writeRow == width-1) {
			writeCol++;
			writeRow = 0;
		}
		else {
			writeRow++;
		}*/
	}

	bm_save(b, "out.gif");

}


/*
* this function reads input from a file, from there it reads the points, stores them in a list so they can be read later
*/
void readPointCloudData(FILE* stream, int* rasterWidth, List* pL){
	//ListInit(pL, sizeof(pcd_t));
	fscanf(stream, "%d", rasterWidth);

	List tempList;
	List* pTempList = &tempList;
	ListInit(pTempList, sizeof(pcd_t));
	printf("got defined the tempList\n");

	pcd_t high; 
	pcd_t* pHigh = &high;
	pcd_t low;  

	Stats s;
	Stats* pS = &s;
	pTempList->stats = pS;

	pcd_t temp;
	pcd_t* pTemp = &temp;
	
	

	fscanf(stream, "%lf %lf %lf", &high.x, &high.y, &high.height); 
	low.x = high.x;		
	low.y = high.y;
	low.height = high.height;


	listAddEnd(pTempList, pHigh);
	pTempList->stats->minX = low.x;
	pTempList->stats->minY = low.y;


	while (fscanf(stream,"%lf %lf %lf", &temp.x, &temp.y, &temp.height) != EOF) { 
		listAddEnd(pTempList,  pTemp);
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
		if (temp.x < pTempList->stats->minX) {
			pTempList->stats->minX = temp.x;
		}
		if (temp.y < pTempList->stats->minY) {
			pTempList->stats->minY = temp.y;
		}
	}

	int m = listInitFull( pL, sizeof(pcd_t), pTempList->size);

	for (int i = 0; i < pTempList->size; i++) {
		pcd_t* temp = listGet(pTempList, i);
		temp->relitiveX = (int)(temp->x - pTempList->stats->minX);
		temp->relitiveY = (int)(temp->y - pTempList->stats->minY);
		int realIndex = temp->relitiveX;
		realIndex *= *rasterWidth;
		realIndex += temp->relitiveY;
		
		listSet(pL, realIndex, temp);
	}

	printf("High point: x = %.1f, y = %.1f, height = %.15f \n", high.x, high.y, high.height); 
	printf("Low point: x = %.1f, y = %.1f, height = %.15f \n", low.x, low.y, low.height);
	pcd_t* tempp = (pcd_t*)listGet(pL, 5);
	printf("the relivtie points for data[0][5] is: %d and %d \n", tempp->relitiveX, tempp->relitiveY);
	
	pL->stats->minX = pTempList->stats->minX;
	pL->stats->minY = pTempList->stats->minY;
	pL->stats->high = high.height;
	pL->stats->low = low.height;

}


int initializeWatershed(pointcloud_t* pc) {
	List* points = pc->points;
	for (int i = 0; i < points->size; i++) {
		pcd_t* p =  (pcd_t*) listGet(points, i);
		p->wd = 0;
		p->north = NULL;
		p->east = NULL;
		p->west = NULL;
		p->south = NULL;
		for (int z = 0; i < points->size; i++) {
			pcd_t* temp = (pcd_t*)listGet(points, z);
			if (temp->x == p->x && temp->y == p->y + 1) {
				p->north = temp;
			}
			else if (temp->x == p->x && temp->y == p->y - 1) {
				p->south = temp;
			}
			else if (temp->y == p->y && temp->x == p->x + 1) {
				p->east = temp;
			}
			else if (temp->y == p->y && temp->x == p->x - 1) {
				p->west = temp;
			}
		}

	}
	return 0;

}

//void watershedAddUniformWater(pointcloud_t* pc, double amount) {
//	List points = pc->points;
//	for (int i = 0; i < points->size; i++) {
//		pcd_t* p = listGet(points, i);
//		p->wd = amount;
//	}
//}
//
//
//void watershedStep(pointcloud_t* pc) {
//	List* points = pc->points;
//	double temps[] = malloc(sizeof(double) * points->size);
//	for (int i = 0; i < points->size, i++) {
//
//		pcd_t* p = listGet(points, i);
//		pcd_t* east = p->east;
//		pcd_t* west = p->west;
//		pcd_t* north = p->north;
//		pcd_t* south = p->south;
//		double temp = (helper(p->height, west->height, p->wd, west->wd) + helper(p->height, east->height, p->wd, east->wd) + helper(p->height, north->height, p->wd, north->wd) + helper(p->height, south->height, p->wd, south->wd)) - p->wd * ecoef;
//		temps[i] = temp;
//	}
//
//	for (int i = 0; i < points->size, i++) {
//		pcd_t* p = listGet(points, i);
//		p->wd = temps[i];
//	}
//}
//
//double helper(double t1, double w1, double t2, double w2) {
//	return ((t2 + w2) - (t1 - w1) * wcoef);
//}
