#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interpretor.h"
#include "structures.h"

// ============================================
// FONCTIONS UTILITAIRES
// ============================================

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

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
// CONVERSION INFIXEE -> POSTFIXEE (Algorithme de Shunting-Yard)
// ============================================

char* infix_to_postfix(char* infix) {
    int len = strlen(infix);
    char* postfix = malloc(sizeof(char) * (len * 2 + 1));
    if(postfix == NULL) return NULL;
    
    int postfix_index = 0;
    
    StackChar* stack = create_stack_char(len);
    if(stack == NULL) {
        free(postfix);
        return NULL;
    }
    
    int parentheses_count = 0;
    int last_was_operator_or_open = 1; // Pour détecter les nombres négatifs
    int operand_count = 0;
    int operator_count = 0;
    
    for(int i = 0; i < len; i++) {
        char current = infix[i];
        
        // 1. Ignorer les espaces
        if(current == ' ') {
            continue;
        }
        
        // 2. Parenthese ouvrante
        if(current == '(') {
            push_char(stack, current);
            parentheses_count++;
            last_was_operator_or_open = 1;
        }
        // 3. Parenthese fermante
        else if(current == ')') {
            parentheses_count--;
            if(parentheses_count < 0) {
                free(postfix);
                free_stack_char(stack);
                return NULL;
            }
            while(!is_empty_char(stack) && peek_char(stack) != '(') {
                postfix[postfix_index++] = pop_char(stack);
                postfix[postfix_index++] = ' ';
            }
            if(!is_empty_char(stack)) {
                pop_char(stack); // Enlever '('
            } else {
                free(postfix);
                free_stack_char(stack);
                return NULL;
            }
            last_was_operator_or_open = 0;
        }
        // 4. Nombre (chiffre ou separateur decimal) ou nombre négatif
        else if(isdigit(current) || current == '.' || current == ',' ||
                (current == '-' && last_was_operator_or_open && 
                 i + 1 < len && (isdigit(infix[i+1]) || infix[i+1] == '.' || infix[i+1] == ','))) {
            
            // Gérer le signe négatif
            if(current == '-' && last_was_operator_or_open) {
                postfix[postfix_index++] = '-';
                i++;
                current = infix[i];
            }
            
            while(i < len && (isdigit(infix[i]) || infix[i] == '.' || infix[i] == ',')) {
                postfix[postfix_index++] = infix[i];
                i++;
            }
            i--;
            postfix[postfix_index++] = ' ';
            last_was_operator_or_open = 0;
            operand_count++;
        }
        // 5. Operateur
        else if(is_operator(current)) {
            while(!is_empty_char(stack) && 
                  is_operator(peek_char(stack)) && 
                  get_priority(peek_char(stack)) >= get_priority(current)) {
                postfix[postfix_index++] = pop_char(stack);
                postfix[postfix_index++] = ' ';
            }
            push_char(stack, current);
            last_was_operator_or_open = 1;
            operator_count++;
        }
        // 6. Caractere invalide
        else {
            free(postfix);
            free_stack_char(stack);
            return NULL;
        }
    }
    
    // Verifier l'equilibre final des parentheses
    if(parentheses_count != 0) {
        free(postfix);
        free_stack_char(stack);
        return NULL;
    }
    
    // Vérifier qu'il y a assez d'opérandes pour les opérateurs
    if(operator_count > 0 && operand_count < operator_count + 1) {
        free(postfix);
        free_stack_char(stack);
        return NULL;
    }
    
    // 7. Depiler les operateurs restants
    while(!is_empty_char(stack)) {
        char op = pop_char(stack);
        if(op == '(') {
            free(postfix);
            free_stack_char(stack);
            return NULL;
        }
        postfix[postfix_index++] = op;
        postfix[postfix_index++] = ' ';
    }
    
    // Nettoyer l'espace final
    while(postfix_index > 0 && postfix[postfix_index - 1] == ' ') {
        postfix_index--;
    }
    postfix[postfix_index] = '\0';
    
    free_stack_char(stack);
    return postfix;
}

// ============================================
// EVALUATION POSTFIXEE
// ============================================

int evaluate_postfix(char* postfix, double* result) {
    if(postfix == NULL || strlen(postfix) == 0) {
        return 0;
    }
    
    int len = strlen(postfix);
    StackDouble* stack = create_stack_double(len);
    if(stack == NULL) {
        return 0;
    }
    
    char buffer[256];
    int buffer_index = 0;
    
    for(int i = 0; i <= len; i++) {
        char current = (i < len) ? postfix[i] : ' ';
        
        if(current == ' ' || i == len) {
            if(buffer_index > 0) {
                // Protection contre le debordement de buffer
                if(buffer_index >= 256) {
                    free_stack_double(stack);
                    return 0;
                }
                
                buffer[buffer_index] = '\0';
                
                // C'est un operateur (un seul caractère et c'est un opérateur)
                if(buffer_index == 1 && is_operator(buffer[0])) {
                    // Verifier qu'il y a au moins 2 operandes
                    if(stack->top < 1) {
                        free_stack_double(stack);
                        return 0;
                    }
                    
                    double op2 = pop_double(stack);
                    double op1 = pop_double(stack);
                    double res = 0.0;
                    
                    switch(buffer[0]) {
                        case '+': res = op1 + op2; break;
                        case '-': res = op1 - op2; break;
                        case '*': res = op1 * op2; break;
                        case '/':
                            if(op2 == 0.0) {
                                free_stack_double(stack);
                                return 0;
                            }
                            res = op1 / op2;
                            break;
                    }
                    
                    push_double(stack, res);
                }
                // C'est un nombre
                else {
                    // Normaliser: virgules -> points
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
        else {
            // Protection contre le debordement
            if(buffer_index < 255) {
                buffer[buffer_index++] = current;
            } else {
                free_stack_double(stack);
                return 0;
            }
        }
    }
    
    // La pile doit contenir exactement 1 element
    if(stack->top != 0) {
        free_stack_double(stack);
        return 0;
    }
    
    *result = pop_double(stack);
    free_stack_double(stack);
    
    return 1;
}