#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "postfix.h"

// ============================================
// PILE DE CARACTÈRES (StackChar) - Implémentation
// ============================================

StackChar* create_stack_char(int capacity) {
    // Allouer la structure de la pile
    StackChar* stack = malloc(sizeof(StackChar));
    // Allouer le tableau de données de la pile
    stack->data = malloc(sizeof(char) * capacity);
    stack->top = -1;       // Pile vide
    stack->capacity = capacity;
    return stack;
}

void push_char(StackChar* stack, char c) {
    // Vérifier s'il y a de la place
    if(stack->top < stack->capacity - 1) {
        stack->data[++stack->top] = c; // Incrémenter 'top' puis insérer
    }
    // Note: Une gestion complète des erreurs nécessiterait de redimensionner la pile ici.
}

char pop_char(StackChar* stack) {
    if(stack->top >= 0) {
        return stack->data[stack->top--]; // Retourner puis décrémenter 'top'
    }
    return '\0'; // Retourne un caractère nul si la pile est vide
}

char peek_char(StackChar* stack) {
    if(stack->top >= 0) {
        return stack->data[stack->top]; // Retourne l'élément sans modifier 'top'
    }
    return '\0';
}

int is_empty_char(StackChar* stack) {
    return stack->top == -1; // Vrai si 'top' est à -1
}

void free_stack_char(StackChar* stack) {
    free(stack->data); // Libérer le tableau de données
    free(stack);       // Libérer la structure de la pile elle-même
}

// ============================================
// PILE DE NOMBRES (StackDouble) - Implémentation
// ============================================

StackDouble* create_stack_double(int capacity) {
    StackDouble* stack = malloc(sizeof(StackDouble));
    stack->data = malloc(sizeof(double) * capacity);
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push_double(StackDouble* stack, double value) {
    if(stack->top < stack->capacity - 1) {
        stack->data[++stack->top] = value;
    }
}

double pop_double(StackDouble* stack) {
    if(stack->top >= 0) {
        return stack->data[stack->top--];
    }
    return 0.0; // Retourne 0.0 si la pile est vide
}

int is_empty_double(StackDouble* stack) {
    return stack->top == -1;
}

void free_stack_double(StackDouble* stack) {
    free(stack->data);
    free(stack);
}

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
            return 1; // Priorité faible (addition/soustraction)
        case '*':
        case '/':
            return 2; // Priorité élevée (multiplication/division)
        default:
            return 0; // Autres (parenthèses, etc.)
    }
}

// ============================================
// CONVERSION INFIXÉE -> POSTFIXÉE (Algorithme de Shunting-Yard)
// ============================================

char* infix_to_postfix(char* infix) {
    int len = strlen(infix);
    // Allouer de l'espace pour le résultat (la taille max est environ le double de l'original + 1)
    char* postfix = malloc(sizeof(char) * (len * 2 + 1));
    int postfix_index = 0;
    
    // La pile est utilisée pour stocker temporairement les opérateurs et les parenthèses
    StackChar* stack = create_stack_char(len);
    int parentheses_count = 0;
    
    for(int i = 0; i < len; i++) {
        char current = infix[i];
        
        // 1. Ignorer les espaces
        if(current == ' ') {
            continue;
        }
        
        // 2. Parenthèse ouvrante
        if(current == '(') {
            push_char(stack, current);
            parentheses_count++;
        }
        // 3. Parenthèse fermante
        else if(current == ')') {
            parentheses_count--;
            // Vérification de parenthèses mal équilibrées (fermeture sans ouverture)
            if(parentheses_count < 0) {
                free(postfix);
                free_stack_char(stack);
                return NULL; // Erreur
            }
            // Dépiler les opérateurs jusqu'à la parenthèse ouvrante
            while(!is_empty_char(stack) && peek_char(stack) != '(') {
                postfix[postfix_index++] = pop_char(stack);
                postfix[postfix_index++] = ' '; // Ajouter un espace comme séparateur de tokens
            }
            // Dépiler la parenthèse ouvrante (ne pas l'ajouter au résultat)
            if(!is_empty_char(stack)) {
                pop_char(stack);
            }
        }
        // 4. Nombre (chiffre ou séparateur décimal)
        else if(isdigit(current) || current == '.' || current == ',') {
            // Lire le nombre entier (multi-chiffres)
            while(i < len && (isdigit(infix[i]) || infix[i] == '.' || infix[i] == ',')) {
                postfix[postfix_index++] = infix[i];
                i++;
            }
            i--; // Remonter l'index car la boucle 'for' va l'incrémenter
            postfix[postfix_index++] = ' '; // Ajouter un espace pour séparer le nombre du prochain token
        }
        // 5. Opérateur
        else if(is_operator(current)) {
            // Dépiler les opérateurs ayant une priorité supérieure ou égale
            while(!is_empty_char(stack) && 
                  is_operator(peek_char(stack)) && 
                  get_priority(peek_char(stack)) >= get_priority(current)) {
                postfix[postfix_index++] = pop_char(stack);
                postfix[postfix_index++] = ' ';
            }
            push_char(stack, current); // Empiler l'opérateur actuel
        }
        // 6. Caractère invalide
        else {
            free(postfix);
            free_stack_char(stack);
            return NULL; // Erreur
        }
    }
    
    // Vérifier l'équilibre final des parenthèses (ouvertes sans fermeture)
    if(parentheses_count != 0) {
        free(postfix);
        free_stack_char(stack);
        return NULL; // Erreur
    }
    
    // 7. Dépiler les opérateurs restants dans la pile
    while(!is_empty_char(stack)) {
        char op = pop_char(stack);
        if(op == '(') {
            free(postfix);
            free_stack_char(stack);
            return NULL; // Erreur : parenthèse ouvrante restante
        }
        postfix[postfix_index++] = op;
        postfix[postfix_index++] = ' ';
    }
    
    // Nettoyer l'espace final s'il y en a un
    if(postfix_index > 0 && postfix[postfix_index - 1] == ' ') {
        postfix_index--;
    }
    postfix[postfix_index] = '\0'; // Terminer la chaîne postfixée
    
    free_stack_char(stack);
    return postfix;
}

// ============================================
// ÉVALUATION POSTFIXÉE
// ============================================

int evaluate_postfix(char* postfix, double* result) {
    if(postfix == NULL) {
        return 0; // Erreur de conversion
    }
    
    int len = strlen(postfix);
    // La pile stocke les opérandes (nombres)
    StackDouble* stack = create_stack_double(len);
    
    char buffer[256]; // Buffer temporaire pour stocker chaque token (nombre ou opérateur)
    int buffer_index = 0;
    
    // Parcourir la chaîne postfixée (jusqu'à la fin + 1 pour traiter le dernier token)
    for(int i = 0; i <= len; i++) {
        char current = (i < len) ? postfix[i] : ' ';
        
        // Un token est terminé par un espace ou la fin de la chaîne
        if(current == ' ' || i == len) {
            if(buffer_index > 0) {
                buffer[buffer_index] = '\0'; // Terminer le token dans le buffer
                
                // C'est un opérateur (token de taille 1)
                if(buffer_index == 1 && is_operator(buffer[0])) {
                    // Pour une opération, on doit avoir au moins 2 opérandes dans la pile
                    if(stack->top < 1) {
                        free_stack_double(stack);
                        return 0; // Erreur: opérande(s) manquant(s)
                    }
                    
                    // L'ordre est important en RPN: op1 est le deuxième, op2 le premier dépilé
                    double op2 = pop_double(stack);
                    double op1 = pop_double(stack);
                    double res = 0.0;
                    
                    // Effectuer l'opération
                    switch(buffer[0]) {
                        case '+': res = op1 + op2; break;
                        case '-': res = op1 - op2; break;
                        case '*': res = op1 * op2; break;
                        case '/':
                            if(op2 == 0.0) {
                                free_stack_double(stack);
                                return 0; // Erreur: Division par zéro
                            }
                            res = op1 / op2;
                            break;
                    }
                    
                    push_double(stack, res); // Empiler le résultat
                }
                // C'est un nombre
                else {
                    // Normaliser: remplacer les virgules par des points pour atof()
                    for(int j = 0; j < buffer_index; j++) {
                        if(buffer[j] == ',') {
                            buffer[j] = '.';
                        }
                    }
                    double value = atof(buffer); // Convertir la chaîne en double
                    push_double(stack, value);
                }
                
                buffer_index = 0; // Réinitialiser le buffer
            }
        }
        // Accumuler les caractères du token en cours
        else {
            buffer[buffer_index++] = current;
        }
    }
    
    // À la fin, la pile doit contenir exactement un seul élément (le résultat)
    if(stack->top != 0) {
        free_stack_double(stack);
        return 0; // Erreur: trop ou pas assez d'opérandes/opérateurs
    }
    
    *result = pop_double(stack); // Stocker le résultat final
    free_stack_double(stack);
    
    return 1; // Succès
}