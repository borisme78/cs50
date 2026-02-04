#include <cs50.h>
#include <stdio.h>
#include <math.h>
bool val_check(long long val1, long long val2)
{
    if (val1 == val2)
    {
        return true;
    }
    else if (val1 != val2)
    {
        return false;
    }
}
void print_numbers()
{
    long long number_cart = get_long_long("Number: ");
    while (number_cart > 0)
    {
        long long last_one = number_cart / 10;
        number_cart = last_one;
        if (number_cart == 0)
        {
            break;
        }
        printf("Number: %lld\n", number_cart);
    }
    printf("Кінець\n");
}
void print_every_n_element_while(long long number, int n)
{
    long long first_numbers = number;

    int count = 0;

    while (first_numbers > 0)
    {
        long long last_number = first_numbers % 10;

        first_numbers = first_numbers / 10;

        count++;

        if (count == n)
        {
            printf("%lld\n", last_number);
            count = 0;
        }
    }
    printf("%lld\n", number);
}
void print_every_n_element_for(long long number, int n)
{
    long long first_numbers = number;

    for (int count = 0; first_numbers > 0;)
    {
        long long last_number = first_numbers % 10;

        first_numbers = first_numbers / 10;

        count++; // count + 1 before check
        if (count == n)
        {
            printf("%lld\n", last_number);
            count = 0;
        }
    }

    printf("%lld\n", number);
}
void print_piramid(int rows)
{
    for (int i = 0; i < rows; i++)
    {
        // 1. Print leading spaces
        for (int j = 0; j < rows - i - 1; j++)
        {
            printf(" ");
        }

        // 2. Print 'a' characters
        // Formula: 2 * i + 1 results in 1, 3, 5...
        for (int k = 0; k < (2 * i + 1); k++)
        {
            printf("a");
        }

        // 3. Move to the next line
        printf("\n");
    }
}

int main(void)
{
    print_numbers();
    print_every_n_element_while(123456789,3);
    print_every_n_element_for(123456789, 3);
    print_piramid(5);

}
