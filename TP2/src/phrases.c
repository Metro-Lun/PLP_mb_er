#include <stdio.h>
#include <string.h>

int main() {
    char nomFichier[100];
    char phrase[100];
    char ligne[512];
    FILE *fichier;
    int total = 0;
    int numLigne = 0;

    printf("Entrez le nom du fichier à lire : ");
    scanf("%99s", nomFichier);

    fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur : impossible d’ouvrir le fichier %s\n", nomFichier);
        return 1;
    }

    getchar(); // consommer le \n laissé par scanf
    printf("Entrez la phrase à rechercher : ");
    fgets(phrase, sizeof(phrase), stdin);
    phrase[strcspn(phrase, "\n")] = '\0'; // enlever le \n final

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        numLigne++;
        int count = 0;
        char *pos = ligne;

        while ((pos = strstr(pos, phrase)) != NULL) {
            count++;
            pos += strlen(phrase);
        }

        if (count > 0) {
            printf("Ligne %d : %d occurrence(s)\n", numLigne, count);
            total += count;
        }
    }

    fclose(fichier);

    printf("\nNombre total d’occurrences de \"%s\" : %d\n", phrase, total);

    return 0;
}
