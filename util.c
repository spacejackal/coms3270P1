#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void *allocateArray(int rows, int columns) {
	malloc(sizeOf(double) * (rows * columns));
}