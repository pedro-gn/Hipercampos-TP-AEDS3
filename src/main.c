#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <utils.h>

#define MAX_LINE_LENGTH  1000


void inputRead(char *inputFileName){
    char line[MAX_LINE_LENGTH];
    int pointsNumber;
    
    int anchorA, anchorB;

    FILE *inputFile  = fopen(inputFileName, "r");
    
    for(int i = 0; ;i++){

        if(!fgets(line, 100, inputFile)){
            break;
        };

        //primeira linha 
        if( i == 0){
            pointsNumber  = atoi( strtok(line, " "));
            anchorA = atoi( strtok(NULL, " "));
            anchorB = atoi( strtok(NULL, " "));
            
            (Point*)malloc(pointsNumber * sizeof(Point));
        }

        
    }


    fclose(inputFile);
}





int main(int argc, char *argv[]){
    int opt;
    char *inputFileName = NULL, *outputFileName = NULL;


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

    inputRead(inputFileName);


    return 0;
}