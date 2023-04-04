#ifndef UTILS.H
#define UTILS.H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

typedef struct point{
    int x,y
} Point;


int cmpPointsY(const void *point1, const void *point2);

bool isAbove(Point anchorA, Point anchorB, Point prevP, Point testP);

void inputRead(char *inputFileName, Point **pointsArray, Point *anchorA, Point *anchorB, int *numberOfPoints );


void outputResult(int result, char *outputFileName);


#endif //UTILS_H