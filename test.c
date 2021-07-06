#include <stdio.h>

int main(void)
{
    printf("Precision = 0\n");
    printf("%10.0x", 0);
    printf("\n");
    printf("Value = 0 and Precision = 0\n");
    printf("%12.10x", 25);
    printf("\n");
    // printf("%.10x", 0);
    // printf("%x", 20032621);
    // printf("%x", 20032621);
    // printf("%x", 20032621);
    // printf("%x", 20032621);

    return (0);
}