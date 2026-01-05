#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interpretor.h"
#include "structures.h"

int main() {
    printf("╔══════════════════════════════════════════╗\n");
    printf("║  ÉVALUATEUR D'EXPRESSIONS ARITHMÉTIQUES  ║\n");
    printf("╚══════════════════════════════════════════╝\n\n");
    printf("Entrez une expression arithmétique (ou 'q' pour quitter)\n");
    printf("Formats acceptés:\n");
    printf("  - Infixe: 3 + 4 * 5, (2 + 3) * 4\n");
    printf("  - Postfixe: 3 4 5 * +, 2 3 + 4 *\n");
    printf("  - Lambda: (lambda x.x * 2) 5, (lambda x.x + (2 * x)) k\n\n");
    
    char* input = calloc(256, sizeof(char));
    Variable* variables = calloc(0, sizeof(Variable));
    int size = 0;
    
    while(1) {
        printf("> ");
        
        if(fgets(input, 256, stdin) == NULL) break;
        
        size_t len = strlen(input);
        if(len > 0 && input[len-1] == '\n') input[len-1] = '\0';

        if(strcmp(input, "q") == 0 || strcmp(input, "quit") == 0) break;

        if(strlen(input) == 0) continue;
        
        char* postfix = NULL;
        int need_free = 0;

        int ck_lambda = check_lambda(&input, &variables, &size);
        if(ck_lambda == 1) {
            continue;
        }

        int ck_variable = check_variable(&input, &variables, &size);
        if(ck_variable == 1) {
            // Détecter si l'expression est déjà en postfixe
            if(is_postfix_expression(input)) {
                // printf("-> Expression détectée: POSTFIXE\n");
                postfix = input; // Utiliser directement l'input
            } else {
                // printf("-> Expression détectée: INFIXE\n");
                // Conversion de l'infixé au postfixé
                postfix = infix_to_postfix(input);
                need_free = 1;
                
                if(postfix == NULL) {
                    printf("Erreur: Expression invalide (problème de syntaxe ou de parenthèses)\n");
                    continue;
                }
                
                // printf("-> Expression postfixée: '%s'\n", postfix);
            }
            
            // Évaluation de l'expression postfixée
            double result;
            if(evaluate_postfix(postfix, &result)) {
                // printf("Résultat: %.2f\n", result);
                printf("%.2f\n", result);
            } else {
                printf("Erreur: Évaluation impossible (opérande(s) manquant(s) ou division par zéro)\n");
            }
            
            if(need_free) {
                free(postfix);
            }
        } else if(ck_variable == 3) {
            continue;
        }
    }
    
    free(input);
    printf("\nAu revoir !\n");
    return 0;
}