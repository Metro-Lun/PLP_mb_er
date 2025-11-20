#include <stdio.h>
#include <string.h>

struct etudiant {
    char nom[50];
    char prenom[50];
    char adresse[100];
    float note;
};

int main() {
    struct etudiant etudiants[5];

    char nom[50];
    char prenom[50];
    char adresse[100];
    float note;

    // Saisie des informations
    for (int i = 0; i < 5; i++) {
        printf("\n=== Étudiant %d ===\n", i + 1);

        printf("Nom : ");
        scanf("%49s", nom);
        strcpy(etudiants[i].nom, nom);

        printf("Prénom : ");
        scanf("%49s", prenom);
        strcpy(etudiants[i].prenom, prenom);

        printf("Adresse : ");
        getchar(); // pour consommer le \n laissé par scanf
        fgets(adresse, sizeof(adresse), stdin);
        adresse[strcspn(adresse, "\n")] = '\0'; // enlève le \n final
        strcpy(etudiants[i].adresse, adresse);

        printf("Note : ");
        scanf("%f", &note);
        etudiants[i].note = note;
    }

    // Affichage des informations
    printf("\n=== Liste des étudiants ===\n");
    for (int i = 0; i < 5; i++) {
        printf("\nÉtudiant %d :\n", i + 1);
        printf("Nom : %s\n", etudiants[i].nom);
        printf("Prénom : %s\n", etudiants[i].prenom);
        printf("Adresse : %s\n", etudiants[i].adresse);
        printf("Note : %.2f\n", etudiants[i].note);
    }

    return 0;
}
