#include <stdio.h>
#include <string.h>

int main() {

    char chaine1[255];
    char chaine2[255];
    char la_concat[512];

    printf("Entrez deux strings à la suite, séparés par ENTREE : \n");
    scanf("%s", chaine1);
    scanf("%s", chaine2);

    // avec string.h
    printf("Longueur de chaine1 : %lu\n", strlen(chaine1));
    printf("Longueur de chaine2 : %lu\n", strlen(chaine2));

    strcpy(la_concat, chaine1);
    strcat(la_concat, chaine2);
    printf("Concaténation des deux chaînes : %s\n", la_concat);
    // printf("Mettre chaine1 dans chaine2 : %s\n", strcpy(chaine2, chaine1));

    // sans string.h
    if(strlen(chaine1) < strlen(chaine2)) {
        int i = 0;
        while(chaine1[i] != '\0') {
            chaine2[i] = chaine1[i];
            i++;
        }
        printf("Mettre chaine1 dans chaine2 : %s\n", chaine2);
    } else if(strlen(chaine2) <= strlen(chaine1)) {
        int i = 0;
        while(chaine2[i] != '\0') {
            chaine1[i] = chaine2[i];
            i++;
        }
        printf("Mettre chaine2 dans chaine1 : %s\n", chaine1);
    }


    return 0;
}