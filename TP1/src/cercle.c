#include <stdio.h>
#include <math.h>

int main() {
    float rayon;
    printf("Saisir un rayon : ");
    scanf("%f", &rayon);

    float aire = rayon * rayon * M_PI;

    printf("L'aire du cercle est %f\n", aire);

    return 0;
}