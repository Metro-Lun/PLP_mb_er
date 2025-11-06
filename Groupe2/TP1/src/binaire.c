#include <stdio.h>
#include <stdlib.h>

int main(){
    int tab[32], nbr, i;  
  
    printf("Entrez le nombre à convertir: ");  
    scanf("%d",&nbr);  

    for(i = 0; nbr > 0; i++){  
        tab[i] = nbr % 2;  
        nbr = nbr / 2;  
    } 
  
    printf("\nLe nombre binaire est = ");

    if (i == 0) {
        printf("0");
    } else {
        for(i = i - 1; i >= 0; i--){  
            printf("%d",tab[i]);  
        } 
    }
    printf("\n");

    return 0;
}