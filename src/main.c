#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/utils.h"

#define MAX_LINE_LENGTH  1000



void printPoints(Point *pointsArray, int numberOfPoints){
    for(int i = 0; i<numberOfPoints; i++){
        printf("%d %d\n", pointsArray[i].x, pointsArray[i].y);
    }
}


void inputRead(char *inputFileName, Point **pointsArray, Point *anchorA, Point *anchorB, int *numberOfPoints ){
    char line[MAX_LINE_LENGTH];
    int tempA, tempB, tempNumberOfpoints;

    FILE *inputFile  = fopen(inputFileName, "r");
    
    for(int i = 0; ;i++){

        if(!fgets(line, MAX_LINE_LENGTH, inputFile)){
            break;
        };

        //primeira linha 
        if(i == 0){
            tempNumberOfpoints = atoi( strtok(line, " "));
            *numberOfPoints = tempNumberOfpoints;

            tempA = atoi( strtok(NULL, " "));
            anchorA-> x = tempA;
            anchorA-> y = 0;

            tempB = atoi( strtok(NULL, " "));
            anchorB-> x =  tempB;
            anchorB-> y = 0;

            *pointsArray = (Point *)malloc(tempNumberOfpoints * sizeof(Point));

        }else{
            (*pointsArray)[i-1].x = atoi( strtok(line, " "));
            (*pointsArray)[i-1].y = atoi( strtok(NULL, " "));
        }

    }

    fclose(inputFile);
}


/* Compara a cordenada y do ponto1 e do ponto2
   retorna >0 se for maior =0 se for menor e <0 se for menor.
*/
int cmpPointsY(const void *point1, const void *point2){
    int y1 = ((Point*)point1) -> y;
    int y2 = ((Point*)point2) -> y;
    return y1 - y2;
}

void bruteForce(Point *pointsArray){

}

int main(int argc, char *argv[]){
    int opt;
    char inputFileName[] = "test.txt";
    char *outputFileName = NULL;

    int numberOfPoints; //need for qsort
    Point anchorA, anchorB; 
    Point *pointsArray = NULL;

    // if ( argc < 5){
    //     fprintf(stderr,"Faltando argumentos! \n");
    //     return 0;
    // }

    // while( (opt = getopt(argc, argv, "i:o:")) > 0 ) {
        
    //     switch ( opt ) {
    //         case 'i':
    //             inputFileName = optarg;
    //             break;
    //         case 'o': 
    //             outputFileName = optarg;
    //             break;
    //         default:
    //             fprintf(stderr, "Opcao invalida `%c'\n", optopt) ;
    //             return -1 ;
    //     }
    // }



    inputRead(inputFileName, &pointsArray, &anchorA, &anchorB, &numberOfPoints);



    qsort(pointsArray, numberOfPoints, sizeof(Point), cmpPointsY);

    printPoints(pointsArray, numberOfPoints);

    free(pointsArray);
    return 0;
}









