#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// void mario(int rows, int columns)
// {
//     for (int r = 0; r < rows; r++)
//     {
//         for (int c = 0; c < columns; c++)
//         {
//             printf("#");
//             if (r == c)
//             {
//                 break;
//             }
//         }
//         printf("\n");
//     }
// }


void mario(int rows, int columns)
{
    for (int r = 0; r < rows; r++)
    {
        for (int j = 0; j < rows - r - 1; j++)
        {
            printf(" ");
        }
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
    int height = 0;
    do
    {
        printf("Height: ");
        if (scanf("%d", &height) != 1)
        {
            while (getchar() != '\n');
        }
        else
        {
            while (getchar() != '\n');
        }
    } while (height <= 1 || height >= 8);
     mario(height, height);
}
