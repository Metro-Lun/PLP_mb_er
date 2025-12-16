#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interpretor.h"

// Fonction pour détecter si l'expression est déjà en notation postfixe
// Une expression est considérée comme postfixe si elle ne contient pas de parenthèses
// et si les opérateurs ne sont jamais entre deux nombres
int is_postfix_expression(const char* expr) {
    int len = strlen(expr);
    int last_was_number = 0;
    
    for(int i = 0; i < len; i++) {
        char c = expr[i];
        
        // Ignorer les espaces
        if(c == ' ') {
            continue;
        }
        
        // Vérifier les parenthèses
        if(c == '(' || c == ')') {
            return 0; // Si parenthèses, c'est infixe
        }
        
        // Si c'est un nombre
        if(isdigit(c) || c == '.' || c == ',') {
            // Consommer tout le nombre
            while(i < len && (isdigit(expr[i]) || expr[i] == '.' || expr[i] == ',')) {
                i++;
            }
            i--; // Reculer d'un caractère car la boucle va incrémenter
            
            // Si le dernier token était aussi un nombre, c'est probablement postfixe
            // En infixe, deux nombres consécutifs seraient invalides
            if(last_was_number) {
                return 1; // Probablement postfixe (ex: "3 4 +")
            }
            last_was_number = 1;
        }
        // Si c'est un opérateur
        else if(c == '+' || c == '-' || c == '*' || c == '/') {
            // Gérer le cas du nombre négatif en infixe
            if(c == '-' && !last_was_number && i + 1 < len && 
               (isdigit(expr[i+1]) || expr[i+1] == '.' || expr[i+1] == ',')) {
                // C'est un nombre négatif, pas un opérateur
                continue;
            }
            
            // Si on a un opérateur après un nombre, et ensuite un nombre,
            // c'est probablement infixe (ex: "3 + 4")
            // En postfixe, on aurait : "3 4 +"
            last_was_number = 0;
        }
    }
    
    // Si on n'a pas détecté de pattern postfixe évident, on suppose infixe
    return 0;
}


// Cette fonction détecte si l'utilisateur a entré une variable
int is_variable() {
    return 0;
}

int main() {
    printf("╔══════════════════════════════════════════╗\n");
    printf("║  ÉVALUATEUR D'EXPRESSIONS ARITHMÉTIQUES  ║\n");
    printf("╚══════════════════════════════════════════╝\n\n");
    printf("Entrez une expression arithmétique (ou 'q' pour quitter)\n");
    printf("Formats acceptés:\n");
    printf("  - Infixe: 3 + 4 * 5, (2 + 3) * 4\n");
    printf("  - Postfixe: 3 4 5 * +, 2 3 + 4 *\n\n");
    
    char input[256];
    
    while(1) {
        printf("> ");
        
        if(fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        size_t len = strlen(input);
        if(len > 0 && input[len-1] == '\n') {
            input[len-1] = '\0';
        }
        
        if(strcmp(input, "q") == 0 || strcmp(input, "quit") == 0) {
            break;
        }
        
        if(strlen(input) == 0) {
            continue;
        }
        
        char* postfix = NULL;
        int need_free = 0;
        
        // Détecter si l'expression est déjà en postfixe
        if(is_postfix_expression(input)) {
            printf("DEBUG - Expression détectée: POSTFIXE\n");
            postfix = input; // Utiliser directement l'input
        } else {
            printf("DEBUG - Expression détectée: INFIXE\n");
            // Conversion de l'infixé au postfixé
            postfix = infix_to_postfix(input);
            need_free = 1;
            
            if(postfix == NULL) {
                printf("Erreur: Expression invalide (problème de syntaxe ou de parenthèses)\n");
                continue;
            }
            
            printf("DEBUG - Expression postfixée: '%s'\n", postfix);
        }
        
        // Évaluation de l'expression postfixée
        double result;
        if(evaluate_postfix(postfix, &result)) {
            printf("Résultat: %.2f\n", result);
        } else {
            printf("Erreur: Évaluation impossible (opérande(s) manquant(s) ou division par zéro)\n");
        }
        
        if(need_free) {
            free(postfix);
        }
    }
    
    printf("\nAu revoir!\n");
    return 0;
}