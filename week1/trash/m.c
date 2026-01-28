#include <stdio.h>
#include <stdbool.h>
#include <string.h>
int main(void)
{
    int rows = 8;
    int columns = 8;
    for(int c = 0; c < columns; c++)
    {
            printf("%d", c);
            printf("|");
    }
    printf("\n");
    for(int r = 1; r < rows; r++)
    {   
        printf("%d", r);
        printf("|");
        for(int c = 0; c < columns; c++)
        {
            if (r==c)
            {
                break;
            }
            printf("#|");
            
        }
        printf("\n");
        for(int u = 0; u < columns; u++)
        {
                printf("--");
        }
        printf("\n");
    }
}