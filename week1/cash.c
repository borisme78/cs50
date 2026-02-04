#include <cs50.h>
#include <stdio.h>
#include <math.h>
int main(void)
{
    float change;
    int count_cents = 0;
    do{
        change = get_float("Change owed: ");
    }
    while(change < 0);

    int cent = round(change * 100);
    while (cent >=25)
    {
        cent = cent - 25;
        count_cents++;
    }
    while(cent >=10)
    {
        cent = cent - 10;
        count_cents++;
    }
    while (cent >=5)
    {
        cent = cent - 5;
        count_cents++;
    }
    while (cent >=1)
    {
        cent = cent - 1;
        count_cents++;
    }
    
    printf("%i\n", count_cents);
}