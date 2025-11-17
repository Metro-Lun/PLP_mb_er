#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int r;
    int g;
    int b;
    int a;
} Couleur;

int main() {

    Couleur colors[100];
    Couleur *used_colors;
    srand(time(NULL));

    for(int i = 0; i < 100; i++) {
        Couleur color;
        color.r = rand() % (254-0+1);
        color.g = rand() % (254-0+1);
        color.b = rand() % (254-0+1);
        color.a = rand() % (254-0+1);
    }

    for(int i = 0; i < 100; i++) {
        // vérifier dans used_colors

        for(int j = 0; ; j++) {
            
        }
    }

    return 0;
}