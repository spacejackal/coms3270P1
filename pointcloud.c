#include <stdio.h>
#include <stdlib.h>
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
void imagePointCloud(pointcloud_t* pc, char* filename) {
	double min = pc->points->stats->low;
	double max = pc->points->stats->high;

	int width = pc->cols;
	double diff = max - min;
	printf("diff is %lf\n", diff);
	pcd_t listTemp;
	pcd_t* pListTemp = &listTemp;
	double temp;
	unsigned int section;
	int height = (pc->points->size / width);

	Bitmap* b = bm_create(width, height);
	int writeRow = 0;
	int writeCol = 0;
	printf("size: %d\n", pc->points->size);

	for (int i = 0; i < pc->points->size; i++) {
		pListTemp = (pcd_t*)listGet(pc->points, i);
		//printf("the point got is : x:%lf y:%lf and height:%lf\n", pListTemp->x, pListTemp->y, pListTemp->height);
		//printf("ssssimage the pc stats are low:%lf and high:%lf \n", pc->points->stats->low, pc->points->stats->high);
		temp = pListTemp->height;
		temp -= min;
		//printf("the height got is after sub low: %lf\n", temp);
		temp /= diff;
		temp *= 256;
		section = (unsigned int)temp;
		section += ((unsigned int)temp << 24);
		section += ((unsigned int)temp << 16);
		section += ((unsigned int)temp << 8);

		bm_set_color(b, section);

		bm_putpixel(b, writeRow, writeCol);
		if (writeRow == width - 1) {
			writeCol++;
			writeRow = 0;
		}
		else {
			writeRow++;
		}
	}

	bm_save(b, filename);

}


/*
* I have sunificantly refacterd this code, now it reads all the points into a temperary list, I then find the lowest x and y value.
* and I find the relitive x and y value of each point and put them into a new list so they are in order
* then that new list is returned
*/
pointcloud_t* readPointCloudData(FILE* stream){
	int width;
	int* pWidth = &width;
	fscanf(stream, "%d", pWidth);

	List tempList;
	List* pTempList = (List*)malloc(sizeof(List));
	ListInit(pTempList, sizeof(pcd_t));

	pcd_t high; 
	pcd_t* pHigh = &high;
	pcd_t low;
	pcd_t* pLow = &low;

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

	for (int i = 0; i < pTempList->size; i++) {
		pcd_t* setter = (pcd_t*)listGet(pTempList, i);
		setter->col = (int)(setter->x - pTempList->stats->minX);
		setter->row = (int)(setter->y - pTempList->stats->minY);
	}


	printf("High point: x = %.1f, y = %.1f, height = %.15f \n", high.x, high.y, high.height); 
	printf("Low point: x = %.1f, y = %.1f, height = %.15f \n", low.x, low.y, low.height);
	

	pTempList->stats->high = high.height;
	pTempList->stats->low = low.height;

	
	pointcloud_t pc;
	pointcloud_t* pPC = malloc(sizeof(pointcloud_t));
	pPC->points = pTempList;
	pPC->cols = width;
	pPC->rows = (pTempList->size / width);
	return pPC;
}

/*
* this initializes the water shed sim by getting all the points to point to eachother;
*/
int initializeWatershed(pointcloud_t* pc) {
	List* points = pc->points;
	int width = pc->cols;
	int row = 0; 
	int col = 0;
	for (int i = 0; i < points->size; i++) {
		pcd_t* p =  (pcd_t*) listGet(points, i);
		p->wd = 0;
		p->north = NULL;
		p->east = NULL;
		p->west = NULL;
		p->south = NULL;
		//printf("numbers of loop id");
		if (row != 0) {
			int temp = ((row - 1) * width) + col;
			p->north = listGet(points, temp);
		}if (row != pc->rows) {
			int temp = ((row + 1) * width) + col;
			p->south = listGet(points, temp);
		} if (col != 0) {
			int temp = ((row) * width) + (col-1);
			p->west = listGet(points, temp);
		} if (col != pc->cols-1) {
			int temp = ((row)*width) + (col + 1);
			p->east = listGet(points, temp);
		}
		col++;
		if (col == (pc->cols)) {
			row++;
			col = 0;
		}

	}
	return 0;

}


/*
* adds an amount of water to every point
*/
void watershedAddUniformWater(pointcloud_t* pc, float amount) {
	List* points = pc->points;
	for (int i = 0; i < points->size; i++) {
		pcd_t* p = listGet(points, i);
		p->wd = amount;
	}
}


void watershedStep(pointcloud_t* pc) {
	double wcoef = pc->wcoef;
	List* points = pc->points;
	int size = pc->points->size;
	printf("the eceof is: %lf and the wecof is: %lf \n", pc->ecoef, pc->wcoef);
	printf("total rows:%d , total cols: %d \n", pc->rows, pc->cols);
	double temps[size];
	for (int i = 0; i < size; i++) {
		pcd_t* p = listGet(pc->points, i);
		pcd_t* east = p->east;
		pcd_t* west = p->west;
		pcd_t* north = p->north;
		pcd_t* south = p->south;
		double temp = 0;
		

		if (p->col != pc->cols-1) {
			temp += (helper(wcoef, p->height, east->height, p->wd, east->wd));
		}

		if (p->row !=pc->rows-1) {
			temp+= (helper(wcoef, p->height, north->height, p->wd, north->wd));

		}
		if (p->col != 0) {
			temp += (helper(wcoef, p->height, west->height, p->wd, west->wd));

		}
		if (p->row != 0) {
			temp += (helper(wcoef, p->height, south->height, p->wd, south->wd));

		}

		//printf("the new water depth is: %lf \n", temp);
		temp -=  (p->wd * pc->ecoef);
		temps[i] = temp;

	}

	for (int i = 0; i < points->size; i++) {
		pcd_t* p = listGet(pc->points, i);
		if (p->wd + temps[i] <= 0) {
			p->wd = 0;
		}
		else {
			p->wd += temps[i];
		}
	}
}

double helper(double wcoef,double t1, double t2, double w1, double w2) {
	double temp;
	//printf("t1:%lf, t2:%lf, w1:%lf, w2:%lf \n", t1, t2, w1, w2);
	temp = (t2 + w2);
	temp -= (t1 + w1);
	temp *= wcoef;
	//printf("wcoef = %lf\n", wcoef);
	
	return temp;
}


void imagePointCloudWater(pointcloud_t* pc, double maxwd, char* filename) {
	double min = pc->points->stats->low;
	double max = pc->points->stats->high;
	printf("max is %lf the min:%lf\n", pc->points->stats->high, pc->points->stats->low);
	int width = pc->cols;
	double diff = max - min;
	printf("diff is %lf\n", diff);
	pcd_t listTemp;
	pcd_t* pListTemp = &listTemp;
	double temp;
	double tempwater;
	unsigned int overflow;
	unsigned int waterSection;
	unsigned int section;
	int height = (pc->points->size / width);

	Bitmap* b = bm_create(width, height);
	int writeRow = 0;
	int writeCol = 0;
	printf("the maxWD is: %lf\n", maxwd);


	for (int i = 0; i < pc->points->size; i++) {
		pListTemp = (pcd_t*)listGet(pc->points, i);
		temp = pListTemp->height;
		temp -= min;
		temp /= diff;
		temp *= 255;

		
		if (pListTemp->wd >= maxwd) {
			section =(unsigned int) 50;
			//section = (unsigned int)255 << 24;
		}
		else if(pListTemp->wd <= 0) {
			section = (unsigned int)temp;
			section += ((unsigned int)(temp) << 24);
			section += ((unsigned int)(temp) << 16);
			section += ((unsigned int)(temp) << 8);
		}
		else {
			tempwater = pListTemp->wd;
			tempwater /= maxwd;
			tempwater *= 255;
			if (temp + tempwater >= 255) {
				section = (unsigned int)255;
			}
			else {
			section = (unsigned int)(temp + tempwater);
		}
			section += ((unsigned int)(temp) << 24);
			section += ((unsigned int)(temp) << 16);
			section += ((unsigned int)(temp) << 8);

		}


		//waterSection = ((unsigned int)tempwater << 24);
		//waterSection += ((unsigned int)tempwater << 16);
		//waterSection += ((unsigned int)tempwater << 8);

		


		bm_set_color(b, section);

		bm_putpixel(b, writeRow, writeCol);
		if (writeRow == width - 1) {
			writeCol++;
			writeRow = 0;
		}
		else {
			writeRow++;
		}
	}
	bm_save(b, filename);

}
