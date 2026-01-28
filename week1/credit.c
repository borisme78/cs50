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
    return suma;
}

bool visa(long long number)
{

    long long cart_numder = number;

    bool invalid_or_valid;

    int cart_digits_count = get_cart_digits_count(cart_numder);

    int cart_digits_sum = get_cart_digits_sum(cart_numder);

    bool greater_ten = cart_digits_sum % 10 == 0;
    bool betwen_13_and_16 = 13 <= cart_digits_count || cart_digits_count <= 16;
    bool first_cart_number_13 = cart_numder / 1000000000000 == 4;
    bool first_cart_number_16 = cart_numder / 1000000000000000 == 4;
    bool first_cart_number_visa = first_cart_number_13 || first_cart_number_16;
    if (greater_ten && betwen_13_and_16 && first_cart_number_visa)
    {
        invalid_or_valid = true;
    }
    else
    {
        invalid_or_valid = false;
    }
    return invalid_or_valid;
}

bool mastercard(long long number_maste)
{
    long long cart_numder = number_maste;

    bool invalid_or_valid;

    int cart_digits_count = get_cart_digits_count(cart_numder);

    int cart_digits_sum = get_cart_digits_sum(cart_numder);

    bool greater_ten = cart_digits_sum % 10 == 0;
    bool betwen_16 = cart_digits_count == 16;
    bool two_first_cart_number_16_mastercard = cart_numder / 100000000000000 == 51 || cart_numder / 100000000000000 == 52 || cart_numder / 100000000000000 == 53 || cart_numder / 100000000000000 == 54 || cart_numder / 100000000000000 == 55;

    if (greater_ten && betwen_16 && two_first_cart_number_16_mastercard)
    {
        invalid_or_valid = true;
    }
    else
    {
        invalid_or_valid = false;
    }
    return invalid_or_valid;
}

bool american_express(long long number_american)
{
    long long cart_numder = number_american;

    bool invalid_or_valid;

    int cart_digits_count = get_cart_digits_count(cart_numder);

    int cart_digits_sum = get_cart_digits_sum(cart_numder);

    bool greater_ten = cart_digits_sum % 10 == 0;
    bool betwen_15 = cart_digits_count == 15;
    bool two_first_cart_number_15_american = cart_numder / 10000000000000 == 34 || cart_numder / 10000000000000 == 37;

    if (greater_ten && betwen_15 && two_first_cart_number_15_american)
    {
        invalid_or_valid = true;
    }
    else
    {
        invalid_or_valid = false;
    }
    return invalid_or_valid;
}
int main(void)
{
    long long number = get_long_long("Number: ");
    bool visa_result = visa(number);
    bool mastercard_result = mastercard(number);
    bool american_express_result = american_express(number);
    
    if (visa_result)
    {
        printf("VISA\n");
    }
    else if (mastercard_result)
    {
        printf("MASTERCARD\n");
    }
    else if (american_express_result)
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}