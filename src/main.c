#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
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
    if (seqIndex == 0 || isAbove(anchorA, anchorB, sequence[seqIndex-1], pointsArray[index])) {
        sequence[seqIndex] = pointsArray[index];
        maxSeq = generateSequences(pointsArray, numberOfPoints, index+1, sequence, seqIndex+1, anchorA, anchorB, maxSeq);
    }
 
    // Gera sequências que não incluem o ponto atual
    maxSeq = generateSequences(pointsArray, numberOfPoints, index+1, sequence, seqIndex, anchorA, anchorB, maxSeq);
};



int main(int argc, char *argv[]){
    int max = 0 ; //resultado

    int opt;
    char *inputFileName = NULL;
    char *outputFileName = NULL;

    int numberOfPoints;
    Point anchorA, anchorB; 
    Point *pointsArray = NULL;

    //medir tempo
    struct rusage start, end;


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


    // le o arquivo
    inputRead(inputFileName, &pointsArray, &anchorA, &anchorB, &numberOfPoints);

    // ordena em ordem crescente os pontos em relacao a cordenada Y
    qsort(pointsArray, numberOfPoints, sizeof(Point), cmpPointsY);

    //array auxiliar para armazenar as sequencias de pontos
    Point sequence[numberOfPoints];


    getrusage(RUSAGE_SELF, &start);
    //gera todas as possibilidades e retorna a maior sequencia
    max = generateSequences(pointsArray, numberOfPoints, 0, sequence, 0, anchorA, anchorB, max);
    getrusage(RUSAGE_SELF, &end);

    printf("Tempo de computacao :\n");
    printf("  CPU time: %.06f sec user, %.06f sec system\n",
           diffUserTime(&start, &end), diffSystemTime(&start, &end));
    printf("%d", max);



    //coloca o resultado no .txt
    outputResult(max, outputFileName);

    free(pointsArray);
    return 0;
}