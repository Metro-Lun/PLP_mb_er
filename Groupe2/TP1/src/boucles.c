#include <stdio.h>

int main() {
    int taille;
    
    do {
        printf("Entrez une taille < 10 : ");
        scanf("%d", &taille);
    } while (taille >= 10 || taille <= 0);

    // Version avec for
    for (int i = 1; i <= taille; i++) {
        if (i == 1) {
            printf("* ");
        } else if (i == 2) {
            printf("* *");
        } else if (i > 2 && i <= taille - 1) {
            for (int j = 1; j <= i; j++) {
                if (j == 1 || j == i) {
                    printf("* ");
                } else {
                    printf("# ");
                }
            }
        } else if (i == taille) {
            for (int j = 1; j <= i; j++) {
                printf("* ");
            }
        }
        printf("\n");
    }


    // Version avec while
    int i = 1;
    while (i <= taille) {
        if (i == 1) {
            printf("* ");
        } else if (i == 2) {
            printf("* *");
        } else if (i > 2 && i <= taille - 1) {
            int j = 1;
            while (j <= i) {
                if (j == 1 || j == i)
                    printf("* ");
                else
                    printf("# ");
                j++;
            }
        } else if (i == taille) {
            int j = 1;
            while (j <= i) {
                printf("* ");
                j++;
            }
        }
        printf("\n");
        i++;
    }

    return 0;
}
