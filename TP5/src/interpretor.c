#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "interpretor.h"
#include "structures.h"

/**
 * Détecte si l'expression est déjà en notation postfixe.
 * 
 * Une expression est considérée comme postfixe si elle ne contient pas de parenthèses
 * et si les opérateurs ne sont jamais entre deux nombres.
 */
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
 * 
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
 * Renvoie le type d'un string donné (si son contenu correspond à un int, un float ou un string).
 */
char* get_type(char** string_value) {
    if(strcspn(*string_value, "_\"\'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != strlen(*string_value))
        return "str";
    else if(strcspn(*string_value, ".,") == strlen(*string_value))
        return "int";
    else if(strcspn(*string_value, ".,") != strlen(*string_value))
        return "float";
    else
        return "other";
}

/**
 * Renvoie le nombre de morceaux d'un string (séparateur : espace).
 */
int get_input_length(char** input) {
    char* input_copy = strdup(*input);
    char* saveptr; // contexte pour strtok
    char* token = strtok_r(input_copy, " ", &saveptr);
    int input_length = 0;
    while(token != NULL) {
        input_length++;
        token = strtok_r(NULL, " ", &saveptr);
    }

    free(input_copy);
    return input_length;
}

/**
 * Remplace les inconnues dans un string par leur valeur à l'aide d'un tableau de variables passé en paramètre.
 * 
 * for_display : pour un string, true s'il faut simplement l'afficher à l'écran, false si on traite une opération
 * (exemple : expressions lambda)
 */
int replace_variables_in_text(char** input, Variable** variables, int* size, int for_display) {
    char* input_copy = strdup(*input);
    char* saveptr; // contexte pour strtok
    char* token = strtok_r(input_copy, " ", &saveptr);
    char* new_buffer = malloc(4096);
    new_buffer[0] = '\0';

    while(token != NULL) {
        char* token_to_add = token;

        Variable* var = find_variable(variables, size, token);

        if(strspn(token, "1234567890.,") != strlen(token) // pas un float
            && strspn(token, "1234567890") != strlen(token) // et pas un int
        ) {
            switch(for_display) {
                case 0 : // pour les expressions lambda
                    if(var != NULL) {
                        if(strcmp(var->type, "str") == 0) {
                            printf("Erreur: un string ne va pas dans une expression lambda !\n");
                            return 1;
                        } else {
                            token_to_add = var->value;
                        }
                    }
                    break;
                case 1 : // pour l'affichage à l'écran uniquement
                    if(var != NULL) {
                        if(get_input_length(input) == 1 && strcmp(var->type, "str") == 0) {
                            printf("%s\n", var->value);
                            return 3;
                        } else {
                            token_to_add = var->value;
                        }
                    } else {
                        if(strcspn(token, "*/+-()") == strlen(token)) { // donc pas un opérateur
                            printf("Erreur: la variable %s n'est pas définie\n", token);
                            return 1;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        
        strcat(new_buffer, token_to_add);
        strcat(new_buffer, " ");

        token = strtok_r(NULL, " ", &saveptr);
    }

    *input = strdup(new_buffer);

    free(input_copy);
    free(new_buffer);
    return 0;
}

/**
 * Cette fonction detecte si l'utilisateur a entre une variable.
 * 
 * Codes de sortie: 
 * 0 - succes (traitement postérieur non nécessaire)
 * 1 - succes (désormais il faut traiter l'opération)
 * 2 - erreur, voir retour à l'écran
 * 3 - retour uniquement pour affichage
 */
int check_variable(char** input, Variable** variables, int* size) {  
    // cas de figure assignation
    if(strcspn(*input, "=") != strlen(*input)) {

        char* input_copy2 = strdup(*input);
        char* token = strtok(input_copy2, " ");
        Variable var_to_add;
        int index = 0;

        char* string_buffer = malloc(1024); // pour prendre en compte d'éventuels espaces de type "Bonjour le monde"
        string_buffer[0] = '\0';

        while(token != NULL) {
            switch(index) {
                case 0 :
                    if(isdigit(token[0])) {
                        printf("Erreur: le nom d'une variable ne doit pas commencer par un nombre\n");
                        return 2;
                    }
                    var_to_add.name = strdup(token);
                    break;
                case 1 :
                    if(strcmp(token, "=") != 0) {
                        printf("Erreur: le symbole \"=\" ne se situe pas au bon endroit\n");
                        return 2;
                    }
                    break;
                default:
                    char* new_type = get_type(&token);
                    if(strcmp(new_type, "other") == 0) {
                        printf("Erreur: la variable doit être un entier, un flottant ou une chaîne de caractères\n");
                        return 2;
                    }
                    var_to_add.type = new_type;

                    if(strcmp(new_type, "str") == 0) {
                        strcat(string_buffer, token);
                        strcat(string_buffer, " ");
                    }
                    else
                        var_to_add.value = strdup(token);
                    break;
            }
            index++;
            token = strtok(NULL, " ");
        }

        if(string_buffer[0] != '\0') { // veut dire que la valeur est un string
            // retirer l'espace en trop
            size_t len = strlen(string_buffer);
            while(string_buffer[len-1] == ' ') {
                len = strlen(string_buffer);
                string_buffer[len-1] = '\0';
            }

            // vérifier l'ouverture et la fermeture du string (guillemets)
            char* temp = malloc(4);

            if(string_buffer[0] != '"' && string_buffer[0] != '\'') {
                strcat(temp, "\"");
                string_buffer = strcat(temp, string_buffer);
            }
            if(string_buffer[len-1] != '\'' && string_buffer[len-1] != '"') {
                strcat(string_buffer, "\"");
            }

            var_to_add.value = strdup(string_buffer);

            free(temp);
        }

        // verifier que la variable n'existe pas deja
        Variable* existing_var = find_variable(variables, size, var_to_add.name);
        if(existing_var == NULL) {
            (*size)++;
            Variable* new_variables = realloc(*variables, sizeof(Variable) * (*size));
            if(variables == NULL) {
                perror("Erreur: impossible de créer une nouvelle variable\n");
                return 2;
            } else {
                new_variables[*size-1] = var_to_add;
                *variables = new_variables;
            }

            printf("Variable %s définie avec la valeur %s (%s)\n", var_to_add.name, var_to_add.value, var_to_add.type);
        } 
        else { // sinon tenter d'en remplacer la valeur
            char* var_type = get_type(&var_to_add.value);
            if(strcmp(var_type, "other") == 0 || strcmp(var_type, existing_var->type) != 0) {
                printf("Erreur: %s est de type %s\n", existing_var->name, existing_var->type);
                return 2;
            }
            
            existing_var->value = strdup(var_to_add.value);
            printf("Variable %s redéfinie avec la valeur %s (%s)\n", existing_var->name, var_to_add.value, existing_var->type);
        }
        return 0;
    }

    else { // remplacer le nom de la variable par sa valeur dans le buffer
        int rep = replace_variables_in_text(input, variables, size, 1);
        if(rep == 1)
            return 2;
        else if(rep == 3)
            return 3;
        else
            return 1;
    }

    return 2;
}

/**
 * Cette fonction détecte si l'utilisateur a entré une variable.
 * 
 * Si rien ne se passe (return 0) alors on passe à la suite, et l'expression input est laissée telle quelle.
 */
int check_lambda(char** input, Variable** variables, int* size) {
    if(strncmp(*input, "(lambda x.", 10) != 0) {
        return 0; // aucune erreur donc tout va bien
    }

    char* input_copy = strdup(*input);

    // partir du point et tout prendre y compris la variable de fin
    char* expression = strchr(input_copy, '.');
    expression++;

    char* variable_space = strrchr(expression, ' ');
    if(variable_space == NULL) {
        printf("Erreur: le format de l'expression lambda est incorrect");
        return 1;
    }

    *variable_space = '\0'; // pour couper en deux
    // virer la dernière parenthèse
    size_t len = strlen(expression);
    if(len > 0) {
        expression[len-1] = '\0';
    } else {
        printf("Erreur: l'allocation mémoire pour l'expression lambda a échoué\n");
        return 1;
    }
    char* variable = variable_space + 1;

    // remplacer les x dans l'expression
    char** expr_p = &expression;

    if(strspn(variable, "1234567890.,") != strlen(variable) // pas un float
        && !isdigit(atoi(variable)) // et pas un int
    ) {
        Variable* existing_var = find_variable(variables, size, variable);
        if(existing_var != NULL) {
            replace_variables_in_text(expr_p, variables, size, 0);
        } else {
            printf("Erreur: la variable %s n'est pas définie\n", variable);
            return 1;
        }
    } else {
        Variable var_temp;
        Variable* var = &var_temp;
        Variable** var_p = &var;
        int temp_size = 1;
        int* size_p = &temp_size;

        var_temp.name = "x";
        var_temp.value = variable;
        if(isdigit(atoi(variable)))
            var_temp.type = "int";
        else
            var_temp.type  = "float";

        replace_variables_in_text(expr_p, var_p, size_p, 0);
    }

    *input = strdup(expression);

    free(input_copy);
    return 0;
}
