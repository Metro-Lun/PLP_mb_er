#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lexer.h"

int add_element(Element** elements, int* size, Element element_to_add) {
    (*size)++;
    
    Element* new_elements = realloc(*elements, sizeof(Element) * (*size));

    if(elements == NULL) {
        perror("realloc");
        return 1;
    } else {
        new_elements[*size-1] = element_to_add;
        *elements = new_elements;
    }

    return 0;
}

int main() {
    Element* elements = calloc(0, sizeof(Element));
    int size = 0;

    char operation[20] = "3,4 + 12";
    char *token = strtok(operation, " ");

    while(token != NULL) {
        Element element;

        size_t operator_index = strcspn(token, "+-*/");

        if(operator_index != strlen(token)) {   // c'est donc un opérateur         
            element.type = OPERATEUR; 
            element.data.operateur = token[0];
            add_element(&elements, &size, element);
        } else {    // c'est donc un opérande
            element.type = OPERANDE;
            Operande operande;
            if(strspn(token, "1234567890.,") == strlen(token)) {
                if(strchr(token, '.') != NULL || strchr(token, ',') != NULL) {
                    for(size_t i = 0; i < strlen(token); i++) {
                        if(token[i] == ',') {
                            token[i] = '.';
                        }
                    }

                    operande.type = FLOTTANT;
                    operande.valeur.flottant = atof(token);
                } else {
                    operande.type = ENTIER;
                    operande.valeur.entier = atoi(token);
                }
                element.data.operande = operande;
                add_element(&elements, &size, element);
            }

        }

        // passer au suivant
        token = strtok(NULL, " ");
    }
    

    // revenir au début et tout afficher
    for(int i = 0; i < size; i++) {
        Element element = elements[i];
        if(element.type == OPERATEUR) {
            printf("Opérateur -> %c\n", element.data.operateur);
        } else if(element.type == OPERANDE) {
            if(element.data.operande.type == ENTIER) {
                printf("Entier -> %d\n", element.data.operande.valeur.entier);
            } else if(element.data.operande.type == FLOTTANT) {
                printf("Flottant -> %lf\n", element.data.operande.valeur.flottant);
            } else {
                perror("Erreur operande\n");
                return 1;
            }
        } else {
            perror("Erreur type\n");
            return 1;
        }
    }

    return 0;
}