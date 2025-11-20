#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int r;
    int g;
    int b;
    int a;
} Couleur;

typedef struct {
    Couleur couleur;
    int occurrences;
} Correspondance;

int main() {
    srand(time(NULL));

    Couleur colors[100];
    Correspondance correspondances[100];
    int latest = 0;

    for(int i = 0; i < 100; i++) {
        Couleur color;
        color.r = rand() % (254-0+1);
        color.g = rand() % (254-0+1);
        color.b = rand() % (254-0+1);
        color.a = rand() % (254-0+1);
        colors[i] = color;
    }

    // parce qu'il faut bien essayer d'avoir au moins deux couleurs identiques...
    colors[12].r = 1;
    colors[12].g = 1;
    colors[12].b = 1;
    colors[12].a = 1;
    
    colors[36].r = 1;
    colors[36].g = 1;
    colors[36].b = 1;
    colors[36].a = 1;

    // faire le tour des couleurs
    for(int i = 0; i < 100; i++) {
        Couleur c = colors[i];
        int found = 0;
        int j = 0;
        
        while(!found && latest > 0 && j < latest) {
            Correspondance corr = correspondances[j];
            Couleur uc = corr.couleur;
            if(c.r == uc.r && c.g == uc.g && c.b == uc.b && c.a == uc.a) {
                correspondances[j].occurrences++;
                found = 1;
            }
            j++;
        }

        if(!found) {
            Correspondance corr;
            corr.couleur = c;
            corr.occurrences = 1;
            correspondances[latest] = corr;
            latest++;
        }
    }

    // affichage
    for(int i = 0; i < latest; i++) {
        Correspondance corr = correspondances[i];
        Couleur c = corr.couleur;
        printf("%d Couleur (%d,%d,%d,%d) : %d occurrence(s)\n", i, c.r, c.g, c.b, c.a, corr.occurrences);
    }

    return 0;
}