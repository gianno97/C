#include <stdio.h>

int main(int argc, char **argv)
{
    char c = '5';
    int n;
    
    n = c;
    printf("Valore int: %d\n", n);
    n = c - '0';
    printf("Valore int: %d\n", n);
    printf("Valore char: %c\n", c);
    
    return 0;
}
