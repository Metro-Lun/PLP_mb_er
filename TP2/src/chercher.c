#include <stdio.h>

/* Compare deux chaînes de caractères sans utiliser strcmp
    Retourne 1 si les deux chaînes sont identiques, 0 sinon */
int comparer(const char *a, const char *b) {
     int i = 0;
     // Parcours caractère par caractère tant que ni 'a' ni 'b' n'ont atteint '\0'
     while (a[i] != '\0' && b[i] != '\0') {
          // Si un caractère diffère, les chaînes sont différentes
          if (a[i] != b[i])
                return 0;
          i++;
     }
     // Les chaînes sont égales uniquement si les deux se terminent en même temps
     return (a[i] == '\0' && b[i] == '\0');
}

int main() {
    char phrases[10][100] = {
        "Bonjour, comment ça va ?",
        "Le temps est magnifique aujourd'hui.",
        "C'est une belle journée.",
        "La programmation en C est amusante.",
        "Les tableaux en C sont puissants.",
        "Les pointeurs en C peuvent être déroutants.",
        "Il fait beau dehors.",
        "La recherche dans un tableau est intéressante.",
        "Les structures de données sont importantes.",
        "Programmer en C, c'est génial."
    };

    char phraseRecherchee[100];
    int trouve = 0;

    printf("Entrez la phrase à rechercher : ");
    fgets(phraseRecherchee, sizeof(phraseRecherchee), stdin);

    // Supprimer le \n à la fin
    int len = 0;
    while (phraseRecherchee[len] != '\0') {
        if (phraseRecherchee[len] == '\n') {
            phraseRecherchee[len] = '\0';
            break;
        }
        len++;
    }

    // Recherche sans strcmp()
    for (int i = 0; i < 10; i++) {
        if (comparer(phrases[i], phraseRecherchee)) {
            trouve = 1;
            break;
        }
    }

    if (trouve)
        printf("Phrase trouvée.\n");
    else
        printf("Phrase non trouvée.\n");

    return 0;
}
