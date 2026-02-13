#include <cs50.h>
#include <stdio.h>
#include <string.h>

float milt_float_number(float a, float b)
{
    float mult = a * b;
    return mult;
}


int add_two_ints(int a, int b)
{
    int sum = a + b;
    return sum;
}


bool valid_triangle(float a, float b, float c)
{
    if (a <= 0 || b <=0 || c <= 0)
    {
        return false;
    }
    if ((a + b <= c) || (a + c <= b) || b + c <= a)
    {
        return false;
    }
    return true;

}

int main(void)
{

int age[] = {12, 34, 56, 55,60,87};
float avarege, sum = 0;
int i;
float length = sizeof(age) / sizeof(age[0]);

for (i = 0; i < length; i++)
{
    sum += age[i];
}
avarege = sum / length;
printf("%f\n", avarege);

milt_float_number(3.5, 2.5);
int l = add_two_ints(2,5);
printf("%d\n", l);

int first;
int second;

int x = get_int("Введіть ціле число: \n");

int y = get_int("Введіть друге ціле число: \n");
int z = add_two_ints(x, y);
printf("Сума: %d + %d = %d\n ",x , y, z);

valid_triangle(3, 3, 3);

int arr [] = [1,2,3,4,5]

for(int i=0; i< length(arr); i++){
    int val = arr[i]
    int replace_val = 9;
    arr[i] = 9;
}

}