#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void mario(int rows, int columns)
{
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < columns; c++)
        {
            printf("#");
            if (r == c)
            {
                break;
            }
        }
        printf("\n");
    }
}

int main(void)
{
    int rows = 0;
    int columns = 0;
    char user_input;
    do
    {
        printf("Enter rows:");
        scanf("%d", &rows);
        printf("Enter columns:");
        scanf("%d", &columns);
        scanf("%c", &user_input);
        mario(rows,columns);
    }while (scanf("%c", &user_input)=='\n');
}
