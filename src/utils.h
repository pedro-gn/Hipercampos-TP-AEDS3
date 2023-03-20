#ifndef UTILS.H
#define UTILS.H

#include <stdbool.h>
#include <stdio.h>


typedef struct point{
    int x,y
} Point;

bool isAbove(Point anchorA, Point anchorB, Point prevP, Point testP);



#endif