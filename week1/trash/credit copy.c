#include <cs50.h>
#include <stdio.h>
#include <math.h>
int number_count(long number)
{
    int count = 0;
    if (number == 0)
    {
        count = 1;
    }
    while (number > 0)
    {
        number /= 10;
        count++;
    }
    printf("%d", count);
    return count;
}
int main(void)
{
    long long cart = 4003600000000014;
    int suma = 0;
    while (cart > 0)
    {
        long last_part = cart % 100;
        cart = cart / 100;
        printf("%lld %lld\n", last_part, cart);
        long first_digit = last_part / 10;
        long second_digit = last_part % 10;
        printf("%lld %lld\n", first_digit, second_digit);

        int pair_digit = first_digit * 2;
        int pair_digit_sum = pair_digit / 10 + pair_digit % 10;
        
        suma += pair_digit_sum + second_digit;
        printf("%d\n", suma);
    }
    printf("\n");
}
