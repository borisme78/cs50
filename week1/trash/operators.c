#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main(void)
{
     int x, y;
     char op, choise[5];
    
    do{
    printf("введіть x:\n");
    scanf("%d", &x);
    printf("введіть y:\n");
    scanf("%d", &y);
    printf("введіть операцію +, -, *, /, %% :\n");
    scanf(" %c", &op);

        switch (op)
    {
        case '+':
            printf("x + y = %d\n", x + y);
            break;
        case '-':
            printf("x - y = %d\n", x - y);
            break;
        case '*':
            printf("x * y = %d\n", x * y);
            break;
        case '/':
            if (y != 0)
                printf("x / y = %d\n", x / y);
            else
                printf("Ділення на нуль неможливе!\n");
            break;
        case '%':
            if (y != 0)
                printf("x %% y = %d\n", x % y);
            else
                printf("Ділення на нуль неможливе!\n");
            break;
        default:
            printf("Невідома операція!\n");
    }
    printf("\n Продовжити? (так/ні): ");
    scanf(" %s", choise);
    }
    while (strcmp(choise, "так") == 0);
return 0;     
}