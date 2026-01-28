#include <cs50.h>
#include <stdio.h>
#include <math.h>
int get_cart_digits_count(long long number)
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
    return count;
}
int get_cart_digits_sum(long long cart)
{
    int suma = 0;
    while (cart > 0)
    {
        long last_part = cart % 100;
        cart = cart / 100;
        long first_digit = last_part / 10;
        long second_digit = last_part % 10;
        int pair_digit = first_digit * 2;
        int pair_digit_sum = pair_digit / 10 + pair_digit % 10;
        suma += pair_digit_sum + second_digit;
    }
    printf("\n");
    return suma;
}

int main(void)

{
    long long cart_numder = 5605105105105100;

    int cart_digits_count = get_cart_digits_count(cart_numder);

    int cart_digits_sum = get_cart_digits_sum(cart_numder);

    printf("cart_digits_count: %d\n", cart_digits_count);
    printf("cart_digits_sum: %d\n", cart_digits_sum);

    bool greater_ten = cart_digits_sum % 10 == 0;
    bool betwen_13_and_16 = 13 <= cart_digits_count || cart_digits_count <= 16;
    bool first_cart_number_13 = cart_numder / 1000000000000 == 4;
    bool first_cart_number_16 = cart_numder / 1000000000000000 == 4;
    bool first_cart_number_visa = first_cart_number_13 || first_cart_number_16;
    bool betwen_16 = cart_digits_count == 16;
    int car_number_chek = cart_numder / 100000000000000;
    bool two_first_cart_number_16_mastercard = cart_numder / 100000000000000 == 51 || 52 || 53 || 54 || 55;
    bool betwen_15 = cart_digits_count == 15;
    bool two_first_cart_number_15_american = cart_numder / 10000000000000 == 34 || 37;

    printf("%d\n", two_first_cart_number_15_american);

    if (greater_ten && betwen_13_and_16 && first_cart_number_visa)
    {
        printf("VISA\n");
    }
    else if (greater_ten && betwen_16 && two_first_cart_number_16_mastercard)
    {
        printf("MASTERCARD\n");
    }
    else if (greater_ten && betwen_15 && two_first_cart_number_15_american)
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}