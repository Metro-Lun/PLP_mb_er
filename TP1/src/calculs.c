#include <stdio.h>

int main() {

    int num1, num2;
    char op;

    printf("Entrez le premier entier :\n");
    scanf("%d", &num1);

    printf("Entrez le deuxième entier :\n");
    scanf("%d", &num2);

    printf("Choisissez parmi : + - * / %% & | ~ \n");
    scanf(" %c", &op);

    switch(op) {
        case '+' :
            printf("%d + %d = %d\n", num1, num2, num1 + num2);
            break;
        case '-' :
            printf("%d - %d = %d\n", num1, num2, num1 - num2);
            break;
        case '*' :
            printf("%d * %d = %d\n", num1, num2, num1 * num2);
            break;
        case '/' :
            if(num2 == 0) {
                printf("Gros nul tu ne peux pas diviser par 0\n");
            } else {
                printf("%d / %d = %d\n", num1, num2, num1 / num2);
            }
            break;
        case '%' :
            printf("%d %% %d = %d\n", num1, num2, num1 % num2);
            break;
        case '&' :
            printf("%d & %d = %d\n", num1, num2, num1 & num2);
            break;
        case '|' :
            printf("%d | %d = %d\n", num1, num2, num1 | num2);
            break;
        case '~' :
            int num;
            printf("Choisissez votre opérande : 1 ou 2 ?\n");
            scanf("%d", &num);

            switch(num) {
                case 1 :
                    printf("~ %d = %d\n", num1, ~num1);
                    break;
                case 2 :
                    printf("~ %d = %d\n", num2, ~num2);
                    break;
                default :
                    printf("soit 1 soit 2...\n");
            }
            break;
        default :
            printf("Gros nul tu ne sais pas écrire\n");
    }

    return 0;
}