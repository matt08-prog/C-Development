#include <stdio.h>

// something is wrong here :(
int swap( int *a, int *b) {
    int temp;

    // temp is now A's value
    temp = *a;

    // The value of A is now the value of B
    *a = *b;

    // The value of B is now A's old value
    *b = temp;

    return 0;
}

int main() {
    int x = 10, y = 20;
    printf("%d %d\n", x, y);
    swap(&x, &y);
    printf("%d %d\n", x, y);
    return 0;
}