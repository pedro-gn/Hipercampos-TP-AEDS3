#include "../include/utils.h"


/* Testa se um ponto esta acima das duas retas formadas pelas ancoras 
e pelo ponto escolhido anteriormente*/
bool isAbove(Point anchorA, Point anchorB, Point prevP, Point testP){


    float m1, b1;
    float m2, b2;


    /*if( anchorA.x == prevP.x ){   
        m2 = (float)(prevP.y - anchorB.y) / (float)(prevP.x - anchorB.x);
        b2 = anchorB.y - (m2 * anchorB.x);

        if( testP.y >= (( m2 * testP.x ) + b2) && testP.x < anchorA.x){
            return true;
        }else{
            return false;
        }

    }else if(anchorB.x == prevP.x){

        m1 = (prevP.y - anchorA.y) / (prevP.x - anchorA.x);
        b1 = anchorA.y - (m1 * anchorA.x);

        if( testP.y >= (( m1 * testP.x ) + b1) && testP.x > anchorB.x){
            return true;
        }else{
            return false;
        }

    }else{
    */


    m1 = (float)(prevP.y - anchorA.y) / (float)(prevP.x - anchorA.x);
    b1 = (float)anchorA.y - (m1 * (float)anchorA.x);
    m2 = (float)(prevP.y - anchorB.y) / (float)(prevP.x - anchorB.x);
    b2 = (float)anchorB.y - (m2 * (float)anchorB.x);

    //checa se o ponto de teste esta acima das duas retas ao mesmo tempo
    if( testP.y >= (( m1 * testP.x ) + b1) && testP.y >= (( m2 * testP.x ) + b2) ){
        return true;
    }else{
        return false;
    }


}