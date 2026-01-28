#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    char name[100];
    printf("Enter name: ");
    scanf("%s", name);
    char last_name[100];
    printf("Enter last name: ");
    scanf("%s", last_name);
    printf("Hello, %s %s\n", name, last_name);
    return 0;
}