#pragma once
#include "structures.h"

// ============================================
// PROTOTYPES DES FONCTIONS PRINCIPALES ET UTILITAIRES
// ============================================

int is_operator(char c);                        // Vérifie si un caractère est un opérateur (+, -, *, /)
int get_priority(char c);                       // Retourne la priorité d'un opérateur
char* infix_to_postfix(char* infix);            // Convertit une expression infixée en expression postfixée (RPN)
int evaluate_postfix(char* postfix, double* result); // Évalue l'expression postfixée
int is_postfix_expression(const char* expr);

Variable* find_variable(Variable** variables, int* size, char* name);
char* get_type(char** string_value);
int get_input_length(char** input);
int replace_variables_in_text(char** input, Variable** variables, int* size, int for_display);
int check_variable(char** input, Variable** variables, int* size);
int check_lambda(char** input, Variable** variables, int* size);
