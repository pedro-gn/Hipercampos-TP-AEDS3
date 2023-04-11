#include "../include/utils.h"



/*
 * Escreve a o resultado do programa em um arquivo de texto com o nome passado
 */
void outputResult(int result, char *outputFileName){
    FILE *outputFile = fopen(outputFileName, "w");
    fprintf(outputFile, "%d", result);
    fclose(outputFile);
}

/* 
 *  Compara a cordenada y do ponto1 e do ponto2
 *  retorna  n>0 se for maior n=0 se for menor e n<0 se for menor.
 *  usada na operacao de qsort
 */
int cmpPointsY(const void *point1, const void *point2){
    int y1 = ((Point*)point1) -> y;
    int y2 = ((Point*)point2) -> y;
    return y1 - y2;
}


/* 
 * Testa se um ponto esta acima das duas retas formadas pelas ancoras 
 * e pelo ponto anterior na sequencia
 */
bool isValidPoint(Point anchorA, Point anchorB, Point prevP, Point testP){


    float m1, b1;
    float m2, b2;


    if( anchorA.x == prevP.x ){  
        // Quando a coordenada x do ponto for a mesma que a da ancora A
        m2 = (float)(prevP.y - anchorB.y) / (float)(prevP.x - anchorB.x);
        b2 = anchorB.y - (m2 * anchorB.x);

        if( testP.y >= (( m2 * testP.x ) + b2) && testP.x < anchorA.x){
            return true;
        }else{
            return false;
        }

    }else if(anchorB.x == prevP.x){
        // Quando a coordenada x do ponto for a mesma que a da ancora B
        m1 = (prevP.y - anchorA.y) / (prevP.x - anchorA.x);
        b1 = anchorA.y - (m1 * anchorA.x);

        if( testP.y >= (( m1 * testP.x ) + b1) && testP.x > anchorB.x){
            return true;
        }else{
            return false;
        }

    }else if(prevP.x > anchorB.x){
        // Quando a coordenada x do ponto for maior que a da ancora B
        m1 = (float)(prevP.y - anchorA.y) / (float)(prevP.x - anchorA.x);
        b1 = (float)anchorA.y - (m1 * (float)anchorA.x);
        m2 = (float)(prevP.y - anchorB.y) / (float)(prevP.x - anchorB.x);
        b2 = (float)anchorB.y - (m2 * (float)anchorB.x);
        
        
        if( testP.y > (( m1 * testP.x ) + b1) && testP.y < (( m2 * testP.x ) + b2) ){
            return true;
        }else{
            return false;
        }
        
        
        
    }else if(prevP.x < anchorA.x){
        // Quando a coordenada x do ponto for menor que a da ancora A

        m1 = (float)(prevP.y - anchorA.y) / (float)(prevP.x - anchorA.x);
        b1 = (float)anchorA.y - (m1 * (float)anchorA.x);
        m2 = (float)(prevP.y - anchorB.y) / (float)(prevP.x - anchorB.x);
        b2 = (float)anchorB.y - (m2 * (float)anchorB.x);
        
        if( testP.y < (( m1 * testP.x ) + b1) && testP.y > (( m2 * testP.x ) + b2) ){
            return true;
        }else{
            return false;
        }
        
    }else{
        //checa se o ponto de teste esta acima das duas retas ao mesmo tempo

        //y = mx + b
        m1 = (float)(prevP.y - anchorA.y) / (float)(prevP.x - anchorA.x);
        b1 = (float)anchorA.y - (m1 * (float)anchorA.x);
        m2 = (float)(prevP.y - anchorB.y) / (float)(prevP.x - anchorB.x);
        b2 = (float)anchorB.y - (m2 * (float)anchorB.x);


        if( testP.y >= (( m1 * testP.x ) + b1) && testP.y >= (( m2 * testP.x ) + b2) ){
            return true;
        }else{
            return false;
        }
    }
}


/*
 * Gera rucursivamente todas as sequencias possiveis de pontos e retorna
 * a quantidade de pontos da maior sequencia gerada.
 * 
 * pointsArray : array dos pontos ordenados em relação a cordenada Y *precisa ser liberado usando free().
 * numberOfPoints : quantidade de pontos.
 * index : index do ponto que a funcao recursiva sera chamada.
 * sequence : array auxiliar para guardar um sequencia de pontos.
 * seqIndex : index no array de sequencia .
 * anchorA : ancora A.
 * anchorB : ancora B.
 * maxSeq : usado para acompanhar o tamanho da maior seq. sempre começa com 0.
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


/*
 * Lê o arquivo de entrada e serve as variaveiss recebidas por parametro com os valores lidos.
 * Obs: pointsArray depois de usado prescisa ser liberado com Free().
 */
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