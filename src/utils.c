#include "../include/utils.h"

/* 
 * Testa se um ponto esta acima das duas retas formadas pelas ancoras 
 * e pelo ponto escolhido anteriormente
 */
bool isAbove(Point anchorA, Point anchorB, Point prevP, Point testP){


    float m1, b1;
    float m2, b2;


    if( anchorA.x == prevP.x ){  
        //quando o ponto esta no mesmo eixo x q a ancora A
        m2 = (float)(prevP.y - anchorB.y) / (float)(prevP.x - anchorB.x);
        b2 = anchorB.y - (m2 * anchorB.x);

        if( testP.y >= (( m2 * testP.x ) + b2) && testP.x < anchorA.x){
            return true;
        }else{
            return false;
        }

    }else if(anchorB.x == prevP.x){
        //quando o ponto esta no mesmo eixo x q a ancora B
        m1 = (prevP.y - anchorA.y) / (prevP.x - anchorA.x);
        b1 = anchorA.y - (m1 * anchorA.x);

        if( testP.y >= (( m1 * testP.x ) + b1) && testP.x > anchorB.x){
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
 * Lê o arquivo de entrada e serve as variadas recebidas por parametro com os valores lidos.
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