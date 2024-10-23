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
	printf("ssssimage the pc stats are low:%lf and high:%lf \n", pc->points->stats->low, pc->points->stats->high);

	int width = pc->cols;
	printf("ssssimage the pc stats are low:%lf and high:%lf \n", pc->points->stats->low, pc->points->stats->high);
	double diff = max - min;
	printf("diff is %lf\n", diff);
	pcd_t listTemp;
	pcd_t* pListTemp = &listTemp;
	double temp;
	unsigned int section;
	int height = (pc->points->size / width);

	printf("image acting wird 5 width%d height %d\n",width, height);
	Bitmap* b = bm_create(width, height);
	printf("image acting wird 6\n");
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
	List l;
	List* pL =(List*) malloc(sizeof(List));
	ListInit(pL, sizeof(pcd_t));
	int width;
	int* pWidth = &width;
	fscanf(stream, "%d", pWidth);

	List tempList;
	List* pTempList = (List*)malloc(sizeof(List));
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
		temp->relitiveY = (int)(width - (int)(temp->y - pTempList->stats->minY));
		int realIndex = temp->relitiveX;
		realIndex *= width;
		realIndex += temp->relitiveY;
		
		listSet(pL, realIndex -1, temp);
	}

	printf("High point: x = %.1f, y = %.1f, height = %.15f \n", high.x, high.y, high.height); 
	printf("Low point: x = %.1f, y = %.1f, height = %.15f \n", low.x, low.y, low.height);
	pcd_t* tempp = (pcd_t*)listGet(pL, 5);
	printf("the relivtie points for data[0][5] is: %d and %d \n", tempp->relitiveX, tempp->relitiveY);
	
	pL->stats = pTempList->stats;
	pL->stats->minY = pTempList->stats->minY;
	pTempList->stats->high = high.height;
	pTempList->stats->low = low.height;
	pL->stats->high = high.height;
	pL->stats->low = low.height;
	
	pointcloud_t pc;
	pointcloud_t* pPC = malloc(sizeof(pointcloud_t));
	pPC->points = pL;
	pPC->cols = width;
	pPC->rows = (pL->size / width);
	return pPC;
}


int initializeWatershed(pointcloud_t* pc) {
	List* points = pc->points;
	int width = pc->cols;
	for (int i = 0; i < points->size; i++) {
		pcd_t* p =  (pcd_t*) listGet(points, i);
		p->wd = 0;
		p->north = NULL;
		p->east = NULL;
		p->west = NULL;
		p->south = NULL;
		if (p->relitiveX != 0) {
			int tempx = p->relitiveX + (p->relitiveY*width);
			p->west = listGet(points, tempx - 1);
		}if (p->relitiveX != pc->cols - 1) {
			int tempx = p->relitiveX + (p->relitiveY*width);
			p->east = listGet(points, tempx + 1);
		}if (p->relitiveY != 0) {
			int tempy = p->relitiveX + ((p->relitiveY-1) * width);
			p->north = listGet(points, tempy);
		}if (p->relitiveY != pc->rows - 1) {
			int tempy = p->relitiveX + ((p->relitiveY + 1) * width);
			p->south = listGet(points, tempy);
		}

	}
	return 0;

}

void watershedAddUniformWater(pointcloud_t* pc, float amount) {
	List* points = pc->points;
	for (int i = 0; i < points->size; i++) {
		pcd_t* p = listGet(points, i);
		p->wd = amount;
	}
}


void watershedStep(pointcloud_t* pc) {
	List* points = pc->points;
	int size = pc->points->size;
	printf("the eceof is: %lf and the wecof is: %lf \n", pc->ecoef, pc->wcoef);
	double* temps[size];
	for (int i = 0; i < points->size; i++) {

		pcd_t* p = listGet(points, i);
		pcd_t* east = p->east;
		pcd_t* west = p->west;
		pcd_t* north = p->north;
		pcd_t* south = p->south;
		double temp = 0;
		if (east != NULL) {
			temp += (helper(pc, p->height, east->height, p->wd, east->wd));
		} if (west != NULL) {
			temp+= (helper(pc, p->height, west->height, p->wd, west->wd));
		} if (north != NULL) {
			temp += (helper(pc, p->height, north->height, p->wd, north->wd));
		} if (south != NULL) {
			temp += (helper(pc, p->height, south->height, p->wd, south->wd));
		}
		temp -=  (p->wd * pc->ecoef);
		temps[i] = &temp;
		printf("the water depth is: %lf and the new offset is: %lf \n", p->wd,temp);
	}

	for (int i = 0; i < points->size; i++) {
		pcd_t* p = listGet(pc->points, i);

		p->wd += *temps[i];
	}
}

double helper(pointcloud_t* pc,double t1, double w1, double t2, double w2) {
	
	return (((t2 + w2) - (t1 - w1)) * pc->wcoef);
}


void imagePointCloudWater(pointcloud_t* pc, double maxwd, char* filename) {
	double min = pc->points->stats->low;
	double max = pc->points->stats->high;
	printf("ssssimage the pc stats are low:%lf and high:%lf \n", pc->points->stats->low, pc->points->stats->high);

	int width = pc->cols;
	printf("ssssimage the pc stats are low:%lf and high:%lf \n", pc->points->stats->low, pc->points->stats->high);
	double diff = max - min;
	printf("diff is %lf\n", diff);
	pcd_t listTemp;
	pcd_t* pListTemp = &listTemp;
	double temp;
	double tempwater;
	unsigned int waterSection;
	unsigned int section;
	int height = (pc->points->size / width);

	Bitmap* b = bm_create(width, height);
	int writeRow = 0;
	int writeCol = 0;


	for (int i = 0; i < pc->points->size; i++) {
		pListTemp = (pcd_t*)listGet(pc->points, i);
		temp = pListTemp->height;
		temp -= min;
		temp /= diff;
		temp *= 256;
		tempwater = pListTemp->wd;
		tempwater /= maxwd;
		tempwater *= 256;
		waterSection = ((unsigned int)temp << 24);
		waterSection += ((unsigned int)temp << 16);
		waterSection += ((unsigned int)temp << 8);

		section = (unsigned int)temp;
		section += ((unsigned int)temp << 24);
		section += ((unsigned int)temp << 16);
		section += ((unsigned int)temp << 8);
		section -= waterSection;

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
