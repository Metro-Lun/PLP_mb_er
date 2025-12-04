#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "postfix.h"

// ============================================
// FONCTIONS POUR LA PILE DE CARACTÈRES
// ============================================

// Créer une pile de caractères
StackChar* create_stack_char(int capacity) {
    StackChar* stack = malloc(sizeof(StackChar));
    stack->data = malloc(sizeof(char) * capacity);
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

// Empiler un caractère
void push_char(StackChar* stack, char c) {
    if(stack->top < stack->capacity - 1) {
        stack->data[++stack->top] = c;
    }
}

// Dépiler un caractère
char pop_char(StackChar* stack) {
    if(stack->top >= 0) {
        return stack->data[stack->top--];
    }
    return '\0';
}

// Voir le sommet de la pile sans dépiler
char peek_char(StackChar* stack) {
    if(stack->top >= 0) {
        return stack->data[stack->top];
    }
    return '\0';
}

// Vérifier si la pile est vide
int is_empty_char(StackChar* stack) {
    return stack->top == -1;
}

// Libérer la mémoire de la pile
void free_stack_char(StackChar* stack) {
    free(stack->data);
    free(stack);
}

// ============================================
// FONCTIONS POUR LA PILE DE NOMBRES (DOUBLE)
// ============================================

// Créer une pile de nombres
StackDouble* create_stack_double(int capacity) {
    StackDouble* stack = malloc(sizeof(StackDouble));
    stack->data = malloc(sizeof(double) * capacity);
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

// Empiler un nombre
void push_double(StackDouble* stack, double value) {
    if(stack->top < stack->capacity - 1) {
        stack->data[++stack->top] = value;
    }
}

// Dépiler un nombre
double pop_double(StackDouble* stack) {
    if(stack->top >= 0) {
        return stack->data[stack->top--];
    }
    return 0.0;
}

// Vérifier si la pile est vide
int is_empty_double(StackDouble* stack) {
    return stack->top == -1;
}

// Libérer la mémoire de la pile
void free_stack_double(StackDouble* stack) {
    free(stack->data);
    free(stack);
}

// ============================================
// FONCTIONS UTILITAIRES
// ============================================

// Vérifier si un caractère est un opérateur
int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Obtenir la priorité d'un opérateur
int get_priority(char c) {
    switch(c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// ============================================
// EXERCICES 4.1 & 4.2 : CONVERSION POSTFIXÉE
// ============================================

// Convertir une expression infixée en notation postfixée (avec support des parenthèses)
char* infix_to_postfix(char* infix) {
    int len = strlen(infix);
    char* postfix = malloc(sizeof(char) * (len * 2 + 1));
    int postfix_index = 0;
    
    StackChar* stack = create_stack_char(len);
    
    // Parcourir l'expression infixée
    for(int i = 0; i < len; i++) {
        char current = infix[i];
        
        // Ignorer les espaces
        if(current == ' ') {
            continue;
        }
        
        // Si c'est une parenthèse ouvrante
        if(current == '(') {
            push_char(stack, current);
        }
        // Si c'est une parenthèse fermante
        else if(current == ')') {
            // Dépiler jusqu'à la parenthèse ouvrante
            while(!is_empty_char(stack) && peek_char(stack) != '(') {
                postfix[postfix_index++] = pop_char(stack);
                postfix[postfix_index++] = ' ';
            }
            // Retirer la parenthèse ouvrante
            if(!is_empty_char(stack)) {
                pop_char(stack);
            }
        }
        // Si c'est un chiffre ou un point (nombre)
        else if(isdigit(current) || current == '.' || current == ',') {
            // Ajouter le nombre complet à la sortie
            while(i < len && (isdigit(infix[i]) || infix[i] == '.' || infix[i] == ',')) {
                postfix[postfix_index++] = infix[i];
                i++;
            }
            i--;
            postfix[postfix_index++] = ' ';
        }
        // Si c'est un opérateur
        else if(is_operator(current)) {
            // Dépiler les opérateurs de priorité supérieure ou égale
            while(!is_empty_char(stack) && 
                  is_operator(peek_char(stack)) && 
                  get_priority(peek_char(stack)) >= get_priority(current)) {
                postfix[postfix_index++] = pop_char(stack);
                postfix[postfix_index++] = ' ';
            }
            push_char(stack, current);
        }
    }
    
    // Dépiler tous les opérateurs restants
    while(!is_empty_char(stack)) {
        postfix[postfix_index++] = pop_char(stack);
        postfix[postfix_index++] = ' ';
    }
    
    // Terminer la chaîne
    if(postfix_index > 0 && postfix[postfix_index - 1] == ' ') {
        postfix_index--;
    }
    postfix[postfix_index] = '\0';
    
    free_stack_char(stack);
    return postfix;
}

// ============================================
// EXERCICE 4.3 : ÉVALUATION POSTFIXÉE
// ============================================

// Évaluer une expression en notation postfixée
double evaluate_postfix(char* postfix) {
    int len = strlen(postfix);
    StackDouble* stack = create_stack_double(len);
    
    char buffer[256];
    int buffer_index = 0;
    
    for(int i = 0; i < len; i++) {
        char current = postfix[i];
        
        // Si c'est un espace, traiter le token dans le buffer
        if(current == ' ' || i == len - 1) {
            if(i == len - 1 && current != ' ') {
                buffer[buffer_index++] = current;
            }
            
            if(buffer_index > 0) {
                buffer[buffer_index] = '\0';
                
                // Si c'est un opérateur
                if(buffer_index == 1 && is_operator(buffer[0])) {
                    // Extraire les deux opérandes
                    double op2 = pop_double(stack);
                    double op1 = pop_double(stack);
                    double result = 0.0;
                    
                    // Calculer selon l'opérateur
                    switch(buffer[0]) {
                        case '+':
                            result = op1 + op2;
                            break;
                        case '-':
                            result = op1 - op2;
                            break;
                        case '*':
                            result = op1 * op2;
                            break;
                        case '/':
                            if(op2 != 0.0) {
                                result = op1 / op2;
                            } else {
                                printf("Erreur: Division par zéro\n");
                                free_stack_double(stack);
                                return 0.0;
                            }
                            break;
                    }
                    
                    push_double(stack, result);
                }
                // Sinon c'est un nombre
                else {
                    // Remplacer les virgules par des points
                    for(int j = 0; j < buffer_index; j++) {
                        if(buffer[j] == ',') {
                            buffer[j] = '.';
                        }
                    }
                    double value = atof(buffer);
                    push_double(stack, value);
                }
                
                buffer_index = 0;
            }
        }
        // Accumuler les caractères dans le buffer
        else {
            buffer[buffer_index++] = current;
        }
    }
    
    // Le résultat final est au sommet de la pile
    double result = pop_double(stack);
    free_stack_double(stack);
    
    return result;
}