#include<stdio.h>

int main() {
    int * const volatile p = 5;  // Corrected initialization
    printf("%d", 5/2+p);  // Dereference p to get the value it points to
    return 0;
}

