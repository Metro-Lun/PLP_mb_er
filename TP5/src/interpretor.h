#pragma once

// ============================================
// DÉFINITION DES STRUCTURES
// ============================================

// Structure pour une pile de caractères (utilisée pour les opérateurs dans la conversion)
typedef struct {
    char* data;    // Tableau pour stocker les éléments
    int top;       // Index du sommet de la pile (-1 si vide)
    int capacity;  // Capacité maximale du tableau
} StackChar;

// Structure pour une pile de nombres doubles (utilisée pour l'évaluation)
typedef struct {
    double* data;  // Tableau pour stocker les nombres doubles
    int top;       // Index du sommet de la pile
    int capacity;  // Capacité maximale du tableau
} StackDouble;

// Structure pour une variable (TP5)
typedef struct {
    char* type;
    char* name;
    char* value;
} Variable;

// ============================================
// PROTOTYPES DES FONCTIONS POUR StackChar
// ============================================

StackChar* create_stack_char(int capacity);      // Crée et initialise une pile de caractères
void push_char(StackChar* stack, char c);        // Empile un caractère
char pop_char(StackChar* stack);                 // Dépile et retourne le caractère au sommet
char peek_char(StackChar* stack);                // Regarde le caractère au sommet sans le dépiler
int is_empty_char(StackChar* stack);             // Vérifie si la pile est vide
void free_stack_char(StackChar* stack);          // Libère la mémoire de la pile

// ============================================
// PROTOTYPES DES FONCTIONS POUR StackDouble
// ============================================

StackDouble* create_stack_double(int capacity);  // Crée et initialise une pile de doubles
void push_double(StackDouble* stack, double value); // Empile un nombre double
double pop_double(StackDouble* stack);           // Dépile et retourne le nombre au sommet
int is_empty_double(StackDouble* stack);         // Vérifie si la pile est vide
void free_stack_double(StackDouble* stack);      // Libère la mémoire de la pile

// ============================================
// PROTOTYPES DES FONCTIONS PRINCIPALES ET UTILITAIRES
// ============================================

int is_operator(char c);                        // Vérifie si un caractère est un opérateur (+, -, *, /)
int get_priority(char c);                       // Retourne la priorité d'un opérateur
char* infix_to_postfix(char* infix);            // Convertit une expression infixée en expression postfixée (RPN)
int evaluate_postfix(char* postfix, double* result); // Évalue l'expression postfixée