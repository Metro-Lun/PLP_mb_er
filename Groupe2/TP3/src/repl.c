#include <stdio.h>
#include <string.h>
#include <time.h>    // Pour la gestion de la date et de l'heure
#include <stdlib.h>  // Pour EXIT_SUCCESS
#include <ctype.h>   // Ajout nécessaire pour tolower()

// --- Définitions globales et prototypes de fonctions ---

// Définition des informations de l'interpréteur de commandes
#define VERSION "1.0.0"
#define NOM_SHELL "SimpleShell"

// Prototype de fonction pour les gestionnaires de commandes
typedef int (*CommandeHandler)(const char*, const char*); // Ajout d'un argument pour le préfixe de commande

// Définition de la structure de commande pour le tableau de commandes
typedef struct {
    const char* nom_en;     // Nom en anglais (ex: "quit")
    const char* nom_fr;     // Nom en français (ex: "quitter")
    CommandeHandler fonction;
    const char* description_en;
    const char* description_fr;
} Commande;


// --- Fonctions de gestion des commandes (Handlers) ---

/**
 * Traite la commande 'quit'/'quitter' : ferme l'interpréteur de commandes.
 * @return 0 pour indiquer l'arrêt de la boucle principale.
 */
int traiter_quit(const char* commande, const char* prefixe) {
    printf("Arrêt de %s...\n", NOM_SHELL);
    return 0; // Le 0 sera interprété dans la boucle main comme un signal d'arrêt
}

/**
 * Affiche la version de l'interpréteur de commandes.
 * @return 1 pour continuer la boucle principale.
 */
int afficher_version(const char* commande, const char* prefixe) {
    printf("%s - Version %s\n", NOM_SHELL, VERSION);
    return 1;
}

/**
 * Affiche l'heure et la date actuelles.
 * @return 1 pour continuer la boucle principale.
 */
int afficher_date(const char* commande, const char* prefixe) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char date_string[64];
    strftime(date_string, sizeof(date_string), "%Y-%m-%d %H:%M:%S", tm_info);
    
    printf("Date et heure actuelles : %s\n", date_string);
    return 1;
}

/**
 * Traite la commande 'echo'/'afficher' et affiche le texte saisi par l'utilisateur.
 * @param commande La commande complète (ex: "echo Hello" ou "afficher Bonjour").
 * @param prefixe Le préfixe de commande utilisé ("echo " ou "afficher ").
 * @return 1 pour continuer la boucle principale.
 */
int traiter_echo(const char* commande, const char* prefixe) {
    size_t len_prefixe = strlen(prefixe);
    const char* texte = commande + len_prefixe; // Saute le préfixe

    // Imprime le texte restant
    if (*texte == '\0') {
        printf("\n");
    } else {
        printf("%s\n", texte);
    }
    return 1;
}

// Déclaration anticipée car 'afficher_aide' l'utilise
int afficher_aide(const char* commande, const char* prefixe); 

// --- Tableau de Commandes Bilingue ---

Commande commandes_disponibles[] = {
    // Note : Pour echo/afficher, on utilise l'espace pour indiquer une commande à argument.
    // L'espace doit être inclus dans la chaîne !
    {"quit", "quitter", traiter_quit, 
     "Stops and exits the command interpreter.", "Arrête et quitte l'interpréteur de commandes."},
    {"version", "version", afficher_version, 
     "Displays the interpreter version.", "Affiche la version de l'interpréteur."},
    {"date", "date", afficher_date, 
     "Displays the current date and time.", "Affiche la date et l'heure actuelles."},
    {"echo ", "afficher ", traiter_echo, // Notez l'espace après echo et afficher
     "Prints the text that follows 'echo ' or 'afficher '.", "Affiche le texte qui suit 'echo ' ou 'afficher '."},
    {"help", "aide", afficher_aide, 
     "Displays this list of commands and their usage.", "Affiche cette liste de commandes et leur utilisation."},
    // Marqueur de fin de tableau
    {NULL, NULL, NULL, NULL, NULL} 
};

/**
 * Affiche la liste des commandes disponibles et leur description.
 * Utilise la description EN ou FR en fonction de la commande utilisée pour demander l'aide.
 * @param commande La commande complète saisie.
 * @param prefixe La commande utilisée ("help" ou "aide").
 * @return 1 pour continuer la boucle principale.
 */
int afficher_aide(const char* commande, const char* prefixe) {
    int est_fr = (strcmp(prefixe, "aide") == 0); // Détermine la langue de l'aide

    if (est_fr) {
        printf("Commandes disponibles pour %s :\n", NOM_SHELL);
        printf("---------------------------------------\n");
    } else {
        printf("Available commands for %s :\n", NOM_SHELL);
        printf("---------------------------------------\n");
    }
    
    for (int i = 0; commandes_disponibles[i].nom_en != NULL; i++) {
        const char* nom_en = commandes_disponibles[i].nom_en;
        const char* nom_fr = commandes_disponibles[i].nom_fr;

        // Formattage pour les commandes avec argument (echo/afficher)
        if (strcmp(nom_en, "echo ") == 0) {
            printf("%-10s / %-10s : %s\n", "echo <text>", "afficher <texte>", (est_fr ? commandes_disponibles[i].description_fr : commandes_disponibles[i].description_en));
        } else {
            // Formattage pour les commandes sans argument
            printf("%-10s / %-10s : %s\n", nom_en, nom_fr, (est_fr ? commandes_disponibles[i].description_fr : commandes_disponibles[i].description_en));
        }
    }
    printf("---------------------------------------\n");
    return 1;
}

// --- Fonctions utilitaires ---

/**
 * Convertit une chaîne en minuscules.
 * @param str La chaîne à modifier.
 */
void to_lower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char) str[i]);
    }
}

// --- Fonction de Traitement Générale ---

/**
 * Recherche et exécute la fonction associée à la commande saisie.
 * @param commande_entree_originale La chaîne de commande complète saisie par l'utilisateur (avec la casse d'origine).
 * @return 0 si la commande était 'quit'/'quitter', 1 sinon.
 */
int executer_commande(char* commande_entree_originale) {
    // Crée une copie pour travailler en minuscules sans modifier l'originale
    char commande_minuscule[1024];
    strncpy(commande_minuscule, commande_entree_originale, 1024);
    to_lower(commande_minuscule);

    for (int i = 0; commandes_disponibles[i].nom_en != NULL; i++) {
        const char* nom_en = commandes_disponibles[i].nom_en;
        const char* nom_fr = commandes_disponibles[i].nom_fr;
        size_t len_en = strlen(nom_en);
        size_t len_fr = strlen(nom_fr);

        // 1. Cas des commandes à argument (echo / afficher)
        // Vérifie si le dernier caractère du nom de commande est un espace
        if (nom_en[len_en - 1] == ' ') {
            
            // Vérifie l'alias EN (ex: "echo test" vs "echo ")
            if (strncmp(commande_minuscule, nom_en, len_en) == 0) {
                return commandes_disponibles[i].fonction(commande_entree_originale, nom_en);
            }
            // Vérifie l'alias FR (ex: "afficher test" vs "afficher ")
            else if (strncmp(commande_minuscule, nom_fr, len_fr) == 0) {
                 return commandes_disponibles[i].fonction(commande_entree_originale, nom_fr);
            }
        } 
        // 2. Cas des commandes sans argument (quit/quitter, version, date, help/aide)
        else {
            // Vérifie l'alias EN
            if (strcmp(commande_minuscule, nom_en) == 0) {
                return commandes_disponibles[i].fonction(commande_entree_originale, nom_en);
            }
            // Vérifie l'alias FR
            else if (strcmp(commande_minuscule, nom_fr) == 0) {
                return commandes_disponibles[i].fonction(commande_entree_originale, nom_fr);
            }
        }
    }

    // Si la boucle est terminée sans trouver de correspondance
    printf("Commande non reconnue. Tapez 'help' ou 'aide' pour voir la liste des commandes.\n");
    return 1; // Continue la boucle
}


// --- Fonction principale (main) ---

int main()
{
    printf("Bienvenue dans %s (v%s). Tapez 'help' ou 'aide' pour la liste des commandes.\n\n", NOM_SHELL, VERSION);
    int continuer = 1;

    while (continuer)
    {
        printf("> ");
        char commande[1024];

        if (fgets(commande, sizeof(commande), stdin) == NULL) {
            break;
        }

        // Enlève le caractère de fin de ligne
        commande[strcspn(commande, "\n")] = 0;

        // Traitement de l'entrée non vide
        if (strlen(commande) > 0) {
            // Passe la chaîne originale pour conserver la casse/ponctuation pour 'echo'/'afficher'
            continuer = executer_commande(commande);
        }
        
        printf("\n");
    }

    return EXIT_SUCCESS;
}