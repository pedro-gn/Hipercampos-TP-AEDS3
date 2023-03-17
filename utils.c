#include <stdbool.h>
#include <stdio.h>

struct Point{
    float x,y;
}typedef Point;

/* testa se um ponto esta acima das duas retas formadas pelas ancoras e o ponto escolhido anteriormente*/
bool isAbove(Point anchorA, Point anchorB, Point prevP, Point testP){


    float m1, b1;
    float m2, b2;

    // trata a execao de o ponto anteriormente escolhido estar na
    // mesma cordenada x que uma das duas ancoras formando uma reta vertical
    // se estiver checa se o ponto esta em cima da outra reta e se a cordena x eh maior que a da ancora B  ou menor que o da ancora A


    if( anchorA.x == prevP.x ){   
        m2 = (prevP.y - anchorB.y) / (prevP.x - anchorB.x);
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

        m1 = (prevP.y - anchorA.y) / (prevP.x - anchorA.x);
        b1 = anchorA.y - (m1 * anchorA.x);
        m2 = (prevP.y - anchorB.y) / (prevP.x - anchorB.x);
        b2 = anchorB.y - (m2 * anchorB.x);

        //checa se o ponto de teste esta acima das duas retas ao mesmo tempo
        if( testP.y >= (( m1 * testP.x ) + b1) && testP.y >= (( m2 * testP.x ) + b2) ){
            return true;
        }else{
            return false;
        }

    }

}

