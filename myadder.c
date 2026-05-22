// myadder.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int a, b, sum;

    if (argc != 3)
    {
        printf("Usage: %s <num1> <num2>\n", argv[0]);
        return 1;
    }

    a = atoi(argv[1]);
    b = atoi(argv[2]);

    sum = a + b;

    printf("Sum = %d\n", sum);

    return 0;
}