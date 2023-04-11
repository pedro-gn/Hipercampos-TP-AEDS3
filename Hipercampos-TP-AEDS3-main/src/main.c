#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

#include "../include/utils.h"


// Calcula tempo do usuario
float diffUserTime(struct rusage *start, struct rusage *end)
{
    return (end->ru_utime.tv_sec - start->ru_utime.tv_sec) +
           1e-6*(end->ru_utime.tv_usec - start->ru_utime.tv_usec);
}

// Calcula tempo do sistema
float diffSystemTime(struct rusage *start, struct rusage *end)
{
    return (end->ru_stime.tv_sec - start->ru_stime.tv_sec) +
           1e-6*(end->ru_stime.tv_usec - start->ru_stime.tv_usec);
}


int main(int argc, char *argv[]){
    int max = 0 ; // Resultado

    // Variaveis i/o
    int opt;
    char *inputFileName = NULL;
    char *outputFileName = NULL;

    // Variaveis do problema
    int numberOfPoints;
    Point anchorA, anchorB; 
    Point *pointsArray = NULL;

    // Medir tempo
    struct rusage startC, endC; // Tempo computação
    struct rusage startIO, endIO; // Tempo io
    struct timeval start, end; // Tempo de relgio

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
    // Le o arquivo
    inputRead(inputFileName, &pointsArray, &anchorA, &anchorB, &numberOfPoints);
    getrusage(RUSAGE_SELF, &endIO);


    // Ordena em ordem crescente os pontos em relacao a cordenada Y.
    qsort(pointsArray, numberOfPoints, sizeof(Point), cmpPointsY);


    // Array auxiliar para armazenar as sequencias de pontos.
    Point sequence[numberOfPoints];


    // Gera todas as possibilidades e retorna a maior sequencia.
    gettimeofday(&start, NULL);
    getrusage(RUSAGE_SELF, &startC);

    max = generateSequences(pointsArray, numberOfPoints, 0, sequence, 0, anchorA, anchorB, max);

    getrusage(RUSAGE_SELF, &endC);
    gettimeofday(&end, NULL);

    printf("Maior sequencia possivel: %d.\n" , max);

    printf("Tempo de computacao :\n");
    printf("  CPU time: %.06f seg user, %.06f seg system\n", diffUserTime(&startC, &endC), diffSystemTime(&startC, &endC));
    
    printf("  Tempo de relogio : %f segundos\n",
    1e-6*((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec)));
    
    printf("Tempo de I/O :\n");
    printf("  CPU time: %.06f seg user, %.06f seg system\n", diffUserTime(&startIO, &endIO), diffSystemTime(&startIO, &endIO));


    // Coloca o resultado no .txt
    outputResult(max, outputFileName);

    // Libera o array de pontos
    free(pointsArray);
    return 0;
}