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

/**
 * Parcourt la structure de Variable en parametre pour determiner si la variable existe
 * Renvoie la variable si elle existe, NULL sinon
 */
Variable* find_variable(Variable** variables, int* size, char* name) {
    for(int i = 0; i < *size; i++) {
        if(strcmp((*variables)[i].name, name) == 0)
            return &(*variables)[i];
    }
    return NULL;
}

/**
 * Cette fonction detecte si l'utilisateur a entre une variable.
 * 
 * Codes de sortie: 
 * 0 - succes, pas d'erreur
 * 1 - n'est pas une variable
 * 2 - assignation erronnee : il faudrait trois champs
 * 3 - token operande invalide
 * 4 - token operateur invalide
 * 5 - erreur realloc
 */
int check_variable(char** input, Variable** variables, int* size) {
    if(strcspn(*input, "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == strlen(*input)) {
        return 1; // n'est pas une variable
    }

    if(strcspn(*input, "=") != strlen(*input))
    { // assignation
        char* token = strtok(*input, " ");
        int input_length = 0;
        while(token != NULL) {
            input_length++;
            token = strtok(NULL, " ");
        }
        if(input_length != 3) return 2;

        token = strtok(*input, " ");
        Variable var_to_add;
        int index = 0;

        while(token != NULL) {
            switch(index) {
                case 0 :
                    if(isdigit(token[0])) return 3;
                    var_to_add.name = token;
                    break;
                case 1 :
                    if(strcmp(token, "=") != 0) return 4;
                    break;
                case 2 :
                    if(strcspn(token, ".,") == strlen(token)) var_to_add.type = "int";
                    else if(strcspn(token, ".,") != strlen(token)) var_to_add.type = "float";
                    else if(strcspn(token, "_\"\'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != strlen(token)) var_to_add.type = "str"; //TODO: verifier balises d'ouverture et de fermeture
                    else return 3;
                    var_to_add.value = token;
                    break;
                default:
                    break;
            }

            index++;
            token = strtok(NULL, " ");
        }

        // verifier que la variable n'existe pas deja
        Variable* existing_var = find_variable(variables, size, var_to_add.name);
        if(existing_var == NULL) {
            (*size)++;
            Variable* new_variables = realloc(*variables, sizeof(Variable) * (*size));
            if(variables == NULL) {
                perror("realloc");
                return 5;
            } else {
                new_variables[*size-1] = var_to_add;
                *variables = new_variables;
            }

            printf("%s\n", var_to_add.name);
        }

        free(existing_var);
    }

    else
    { // remplacer le nom de la variable par sa valeur
        char* token = strtok(*input, " ");
        char new_buffer[256];
        int new_buffer_index = 0;

        while(token != NULL) {
            char* token_to_add;
            if(strcspn(token, "_\"\'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != strlen(token)) {
                Variable* var = find_variable(variables, size, token);
            } else {
                token_to_add = token;
            }

            // TODO: new_buffer += token_to_add;
            token = strtok(NULL, " ");
        }
    }

    return 1;
}

int main() {
    printf("╔══════════════════════════════════════════╗\n");
    printf("║  ÉVALUATEUR D'EXPRESSIONS ARITHMÉTIQUES  ║\n");
    printf("╚══════════════════════════════════════════╝\n\n");
    printf("Entrez une expression arithmétique (ou 'q' pour quitter)\n");
    printf("Formats acceptés:\n");
    printf("  - Infixe: 3 + 4 * 5, (2 + 3) * 4\n");
    printf("  - Postfixe: 3 4 5 * +, 2 3 + 4 *\n\n");
    
    char* input = calloc(256, sizeof(char));
    Variable* variables = calloc(0, sizeof(Variable));
    int size = 0;
    
    while(1) {
        printf("> ");
        
        if(fgets(input, sizeof(input), stdin) == NULL) break;
        
        size_t len = strlen(input);
        if(len > 0 && input[len-1] == '\n') input[len-1] = '\0';

        if(strcmp(input, "q") == 0 || strcmp(input, "quit") == 0) break;

        if(strlen(input) == 0) continue;
        
        char* postfix = NULL;
        int need_free = 0;

        // Détecter s'il s'agit d'une variable TODO:
        check_variable(&input, &variables, &size); // TODO: ajouter pointeurs vers la structure Variables et input
        
        // Détecter si l'expression est déjà en postfixe
        if(is_postfix_expression(input)) {
            printf("-> Expression détectée: POSTFIXE\n");
            postfix = input; // Utiliser directement l'input
        } else {
            printf("-> Expression détectée: INFIXE\n");
            // Conversion de l'infixé au postfixé
            postfix = infix_to_postfix(input);
            need_free = 1;
            
            if(postfix == NULL) {
                printf("Erreur: Expression invalide (problème de syntaxe ou de parenthèses)\n");
                continue;
            }
            
            printf("-> Expression postfixée: '%s'\n", postfix);
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