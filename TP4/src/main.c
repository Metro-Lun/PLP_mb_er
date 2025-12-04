#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "postfix.h"

int main() {
    printf("╔════════════════════════════════════════╗\n");
    printf("║  ÉVALUATEUR D'EXPRESSIONS ARITHMÉTIQUES║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    printf("Entrez une expression arithmétique (ou 'q' pour quitter)\n");
    printf("Exemples: 3 + 4 * 5, (2 + 3) * 4, 10 / (2 + 3)\n\n");
    
    char input[256];
    
    while(1) {
        printf("> ");
        
        if(fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        // Retirer le '\n'
        size_t len = strlen(input);
        if(len > 0 && input[len-1] == '\n') {
            input[len-1] = '\0';
        }
        
        // Quitter si 'q'
        if(strcmp(input, "q") == 0 || strcmp(input, "quit") == 0) {
            break;
        }
        
        // Ignorer les lignes vides
        if(strlen(input) == 0) {
            continue;
        }
        
        // Convertir en notation postfixée
        char* postfix = infix_to_postfix(input);
        
        // Évaluer l'expression
        double result = evaluate_postfix(postfix);
        
        // Afficher le résultat
        printf("%.2f\n", result);
        
        free(postfix);
    }
    
    printf("\nAu revoir!\n");
    return 0;
}