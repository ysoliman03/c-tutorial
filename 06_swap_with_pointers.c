/*
 * Example 06: Why Pointers Exist -- Modifying Variables in Functions
 * 
 * C passes arguments by VALUE. Functions get COPIES of your variables,
 * so modifying them inside the function doesn't affect the originals.
 *
 * Pointers solve this: pass the ADDRESS of a variable, and the function
 * can reach back through that address to modify the original.
 *
 * Expected output:
 *   Before:            x=1, y=2
 *   After broken_swap: x=1, y=2   <-- unchanged (only copies were swapped)
 *   After real_swap:   x=2, y=1   <-- actually swapped!
 */

#include <stdio.h>

void broken_swap(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    // only swaps the COPIES -- original variables untouched
}

void real_swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    // modifies the originals through pointers
}

int main(void) {
    int x = 1, y = 2;

    printf("Before:            x=%d, y=%d\n", x, y);

    broken_swap(x, y);
    printf("After broken_swap: x=%d, y=%d\n", x, y);   // still 1, 2

    real_swap(&x, &y);   // pass ADDRESSES, not values
    printf("After real_swap:   x=%d, y=%d\n", x, y);   // now 2, 1

    return 0;
}
