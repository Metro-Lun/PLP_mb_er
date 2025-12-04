#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parseur.h"
#include "evaluation.h"

char* menu() {
    char* operation = malloc(100);

    printf("> ");
    fgets(operation, 100, stdin);
    operation[strcspn(operation, "\n")] = 0;    // retirer le \n

    return operation;
}

int main() {
    printf("Entrez votre opération (séparée par des espaces).\nEntrez q pour quitter.\n");
    while(1) {
        char* op = menu();
        if(!strcmp(op, "q")) {
            break;
        }
        Element* elements = lex(op);
        Expression expr = parse(elements);
        evaluate(expr);
    }
}