#include <stdio.h>
#include "parseur.h"

Expression parse(Element* elements) {
    Expression expr;
    expr.op1_initialized = 0;

    for(int i = 0; i < 3; i++) {
        Element element = elements[i];
        if(element.type == OPERATEUR) {
            expr.operateur = element.data.operateur;
        } else if(element.type == OPERANDE) {
            if(!expr.op1_initialized) {
                expr.operande1 = element.data.operande;
                expr.op1_initialized = 1;
            } else {
                expr.operande2 = element.data.operande;
            }
        }
    }

    return expr;
}

