#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "../include/utils.h"


float diffUserTime(struct rusage *start, struct rusage *end)
{
    return (end->ru_utime.tv_sec - start->ru_utime.tv_sec) +
           1e-6*(end->ru_utime.tv_usec - start->ru_utime.tv_usec);
}

float diffSystemTime(struct rusage *start, struct rusage *end)
{
    return (end->ru_stime.tv_sec - start->ru_stime.tv_sec) +
           1e-6*(end->ru_stime.tv_usec - start->ru_stime.tv_usec);
}


/*
 * Gera rucursivamente todas as sequencias possiveis de pontos e retorna
 * a quantidade de pontos da maior sequencia gerada.
 * 
 * pointsArray : array dos pontos ordenados em relação a cordenada Y *precisa ser liberado usando free()
 * numberOfPoints : quantidade de pontos
 * index : index do ponto que a funcao recursiva sera chamada
 * sequence : array auxiliar para guardar um sequencia de pontos
 * seqIndex : index no array de sequencia 
 * anchorA : ancora A
 * anchorB : ancora B
 */
int generateSequences(Point *pointsArray, int numberOfPoints, int index, Point sequence[], int seqIndex, Point anchorA, Point anchorB, int maxSeq){

    if (index >= numberOfPoints) {
        
        if(seqIndex > maxSeq){
            maxSeq = seqIndex;
        }

        return maxSeq;
    }

    
    // Gera uma sequência que inclui o ponto atual
    if (seqIndex == 0 || isValidPoint(anchorA, anchorB, sequence[seqIndex-1], pointsArray[index])) {
        sequence[seqIndex] = pointsArray[index];
        maxSeq = generateSequences(pointsArray, numberOfPoints, index+1, sequence, seqIndex+1, anchorA, anchorB, maxSeq);
    }
 
    // Gera sequências que não incluem o ponto atual
    maxSeq = generateSequences(pointsArray, numberOfPoints, index+1, sequence, seqIndex, anchorA, anchorB, maxSeq);
};



int main(int argc, char *argv[]){
    int max = 0 ; //resultado

    //variaveis i/o
    int opt;
    char *inputFileName = NULL;
    char *outputFileName = NULL;

    //variaveis do problema
    int numberOfPoints;
    Point anchorA, anchorB; 
    Point *pointsArray = NULL;

    //medir tempo
    struct rusage startC, endC;
    struct rusage startIO, endIO;
    struct timeval start, end;

    if ( argc < 5){
        fprintf(stderr,"Faltando argumentos! \n");
        return 0;
    }

    while( (opt = getopt(argc, argv, "i:o:")) > 0 ) {
        
        switch ( opt ) {
            case 'i':
                inputFileName = optarg;
                break;
            case 'o': 
                outputFileName = optarg;
                break;
            default:
                fprintf(stderr, "Opcao invalida `%c'\n", optopt) ;
                return -1 ;
        }
    }

    getrusage(RUSAGE_SELF, &startIO);

    // le o arquivo
    inputRead(inputFileName, &pointsArray, &anchorA, &anchorB, &numberOfPoints);

    getrusage(RUSAGE_SELF, &endIO);



    // ordena em ordem crescente os pontos em relacao a cordenada Y
    qsort(pointsArray, numberOfPoints, sizeof(Point), cmpPointsY);

    //array auxiliar para armazenar as sequencias de pontos
    Point sequence[numberOfPoints];


    gettimeofday(&start, NULL);
    getrusage(RUSAGE_SELF, &startC);

    //gera todas as possibilidades e retorna a maior sequencia
    max = generateSequences(pointsArray, numberOfPoints, 0, sequence, 0, anchorA, anchorB, max);


    getrusage(RUSAGE_SELF, &endC);
    gettimeofday(&end, NULL);


    printf("Tempo de computacao :\n");
    printf("  CPU time: %.06f seg user, %.06f seg system\n", diffUserTime(&startC, &endC), diffSystemTime(&startC, &endC));
    
    printf("  Tempo de relogio : %f segundos\n",
    1e-6*((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));
    
    printf("Tempo de I/O :\n");
    printf("  CPU time: %.06f seg user, %.06f seg system\n", diffUserTime(&startIO, &endIO), diffSystemTime(&startIO, &endIO));




    //coloca o resultado no .txt
    outputResult(max, outputFileName);

    free(pointsArray);
    return 0;
}