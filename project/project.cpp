#include <stdio.h>

int main() {
    int a = 3, b = 5;
    printf("%d, %d", ++a, (b++, ++b));
    return 0;
}