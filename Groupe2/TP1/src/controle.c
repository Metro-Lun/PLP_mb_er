#include <stdio.h>

int main() {

    for(int i = 1; i <= 1000; i++) {
        if(i%4 == 0 && i%6 != 0) {
            printf("%d est divisible par 4 mais pas par 6\n", i);
        }

        if(i%2 == 9 && i%8 == 0) {
            printf("%d est pair et divisible par 8\n", i);
        }

        if((i%5 == 0 || i%7 == 0) && i%10 != 0) {
            printf("%d est divisible par 5 ou 7 mais pas par 10\n", i);
        }
    }

    return 0;
}