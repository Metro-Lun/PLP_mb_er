#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "postfix.h"

int main() {
    // Affichage d'une interface simple
    printf("╔══════════════════════════════════════════╗\n");
    printf("║  ÉVALUATEUR D'EXPRESSIONS ARITHMÉTIQUES  ║\n");
    printf("╚══════════════════════════════════════════╝\n\n");
    printf("Entrez une expression arithmétique (ou 'q' pour quitter)\n");
    printf("Exemples: 3 + 4 * 5, (2 + 3) * 4, 10 / (2 + 3)\n\n");
    
    char input[256]; // Buffer pour stocker l'entrée de l'utilisateur
    
    while(1) {
        printf("> ");
        
        // Lire l'entrée de l'utilisateur (inclut le caractère '\n')
        if(fgets(input, sizeof(input), stdin) == NULL) {
            break; // Sortir en cas d'erreur de lecture
        }
        
        // Supprimer le caractère de nouvelle ligne '\n' (s'il existe)
        size_t len = strlen(input);
        if(len > 0 && input[len-1] == '\n') {
            input[len-1] = '\0';
        }
        
        // Vérifier si l'utilisateur veut quitter
        if(strcmp(input, "q") == 0 || strcmp(input, "quit") == 0) {
            break;
        }
        
        // Ignorer les entrées vides
        if(strlen(input) == 0) {
            continue;
        }
        
        // 1. Conversion de l'infixé au postfixé (alloue de la mémoire)
        char* postfix = infix_to_postfix(input);
        
        if(postfix == NULL) {
            printf("Erreur: Expression invalide (problème de syntaxe ou de parenthèses)\n");
            continue;
        }
        
        // 2. Évaluation de l'expression postfixée
        double result;
        if(evaluate_postfix(postfix, &result)) {
            // Affichage du résultat avec deux décimales
            printf("Résultat: %.2f\n", result);
        } else {
            // Affiche l'erreur si l'évaluation a échoué (division par zéro, etc.)
            printf("Erreur: Évaluation impossible (opérande(s) manquant(s) ou division par zéro)\n");
        }
        
        // Libérer la mémoire allouée par infix_to_postfix
        free(postfix);
    }
    
    printf("\nAu revoir!\n");
    return 0;
}