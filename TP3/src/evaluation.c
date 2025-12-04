#include <stdio.h>
#include "parseur.h"

void evaluate(Expression expression) {
    Operande op1 = expression.operande1;
    Operande op2 = expression.operande2;

    switch(expression.operateur) {
        case '+' :
            if(op1.type == ENTIER && op2.type == ENTIER) {
                printf("%d\n", op1.valeur.entier + op2.valeur.entier);
            } else if(op1.type == ENTIER && op2.type == FLOTTANT) {
                printf("%f\n", op1.valeur.entier + op2.valeur.flottant);
            } else if(op1.type == FLOTTANT && op2.type == ENTIER) {
                printf("%f\n", op1.valeur.flottant + op2.valeur.entier);
            } else if(op1.type == FLOTTANT && op2.type == FLOTTANT) {
                printf("%f\n", op1.valeur.flottant + op2.valeur.flottant);
            } else {
                printf("Erreur d'addition\n");
            }
            break;
        case '-' :
            if(op1.type == ENTIER && op2.type == ENTIER) {
                printf("%d\n", op1.valeur.entier - op2.valeur.entier);
            } else if(op1.type == ENTIER && op2.type == FLOTTANT) {
                printf("%f\n", op1.valeur.entier - op2.valeur.flottant);
            } else if(op1.type == FLOTTANT && op2.type == ENTIER) {
                printf("%f\n", op1.valeur.flottant - op2.valeur.entier);
            } else if(op1.type == FLOTTANT && op2.type == FLOTTANT) {
                printf("%f\n", op1.valeur.flottant - op2.valeur.flottant);
            } else {
                printf("Erreur de soustraction\n");
            }
            break;
        case '*' :
        if(op1.type == ENTIER && op2.type == ENTIER) {
                printf("%d\n", op1.valeur.entier * op2.valeur.entier);
            } else if(op1.type == ENTIER && op2.type == FLOTTANT) {
                printf("%f\n", op1.valeur.entier * op2.valeur.flottant);
            } else if(op1.type == FLOTTANT && op2.type == ENTIER) {
                printf("%f\n", op1.valeur.flottant * op2.valeur.entier);
            } else if(op1.type == FLOTTANT && op2.type == FLOTTANT) {
                printf("%f\n", op1.valeur.flottant * op2.valeur.flottant);
            } else {
                printf("Erreur de multiplication\n");
            }
            break;
        case '/' : 
            if(op2.valeur.entier == 0 || op2.valeur.flottant == 0.0) {
                printf("Erreur division par 0\n");
                break;
            }

            if(op1.type == ENTIER && op2.type == ENTIER) {
                printf("%f\n", (float) op1.valeur.entier / op2.valeur.entier);
            } else if(op1.type == ENTIER && op2.type == FLOTTANT) {
                printf("%f\n", op1.valeur.entier / op2.valeur.flottant);
            } else if(op1.type == FLOTTANT && op2.type == ENTIER) {
                printf("%f\n", op1.valeur.flottant / op2.valeur.entier);
            } else if(op1.type == FLOTTANT && op2.type == FLOTTANT) {
                printf("%f\n", op1.valeur.flottant / op2.valeur.flottant);
            } else {
                printf("Erreur de division\n");
            }
            break;
        default :
            printf("Erreur : l'opération indiquée n'existe pas\n");
    }
}