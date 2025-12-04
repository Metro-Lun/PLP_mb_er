#pragma once

// Structure pour la pile d'opérateurs (caractères)
typedef struct {
    char* data;
    int top;
    int capacity;
} StackChar;

// Structure pour la pile d'opérandes (nombres)
typedef struct {
    double* data;
    int top;
    int capacity;
} StackDouble;

// Fonctions pour la pile de caractères
StackChar* create_stack_char(int capacity);
void push_char(StackChar* stack, char c);
char pop_char(StackChar* stack);
char peek_char(StackChar* stack);
int is_empty_char(StackChar* stack);
void free_stack_char(StackChar* stack);

// Fonctions pour la pile de nombres
StackDouble* create_stack_double(int capacity);
void push_double(StackDouble* stack, double value);
double pop_double(StackDouble* stack);
int is_empty_double(StackDouble* stack);
void free_stack_double(StackDouble* stack);

// Fonctions pour la conversion et l'évaluation
int is_operator(char c);
int get_priority(char c);
char* infix_to_postfix(char* infix);
double evaluate_postfix(char* postfix);