#include <stdio.h>
#include <stdbool.h>


int main(void)
{
    bool t1 = false;
    bool t2 = false;
    if (t1 || t2)
    {
        printf("t is true\n");
    }
    else if (t1 && t2)
    {
        printf("t is true\n");
    }
    else
    {
        printf("t is false\n");
    }
    printf("t = %d\n", t);
    return 0;
}
