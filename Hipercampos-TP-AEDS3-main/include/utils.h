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

bool isValidPoint(Point anchorA, Point anchorB, Point prevP, Point testP);

int generateSequences(Point *pointsArray, int numberOfPoints, int index, Point sequence[], int seqIndex, Point anchorA, Point anchorB, int maxSeq);

void inputRead(char *inputFileName, Point **pointsArray, Point *anchorA, Point *anchorB, int *numberOfPoints );

void outputResult(int result, char *outputFileName);


#endif //UTILS_H