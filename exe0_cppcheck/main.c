#include <stdio.h>

#define NUM_ELEMENTS 5

int multiplyNumbers(int x, int y) {
    int product = x * y;
    return product;
}

int main(void) {
    int a = 0;
    int b = 5;

    int result = multiplyNumbers(a, b);

    int arr[NUM_ELEMENTS];
    int sum = 0;

    for (int i = 0; i < NUM_ELEMENTS; i++) {
        arr[i] = i;
        sum += arr[i];  
    }

    (void)result;
    (void)sum;

    return 0;
}