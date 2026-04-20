/*
 * Example 08: Dynamic Memory with malloc and free
 * 
 * Static arrays require you to know the size at compile time. malloc lets
 * you request memory AT RUNTIME -- exactly as much as you need.
 *
 * Steps:
 *   1. Ask the OS for N bytes       -> malloc(N * sizeof(int))
 *   2. Check for NULL (malloc can fail)
 *   3. Use the memory like an array -> numbers[i] = ...
 *   4. Give it back                  -> free(numbers)
 *   5. Clear the pointer             -> numbers = NULL
 *
 * Example run:
 *   How many numbers? 5
 *   0 1 4 9 16
 *
 * The three pointer rules this illustrates:
 *   - Initialize every pointer (here, via malloc)
 *   - Check before dereferencing (the NULL check)
 *   - Match every malloc with exactly one free
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n;
    printf("How many numbers? ");
    scanf("%d", &n);        // note the & -- scanf needs an ADDRESS to write to

    // Ask the OS for n integers' worth of memory
    int *numbers = (int*) malloc(n * sizeof(int));

    if (numbers == NULL) {           // malloc returns NULL if it fails
        printf("Allocation failed\n");
        return 1;
    }

    // Fill it with squares
    for (int i = 0; i < n; i++) {
        numbers[i] = i * i;          // use it just like a normal array
    }

    // Print it
    for (int i = 0; i < n; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    free(numbers);                   // MUST give it back when done
    numbers = NULL;                  // good hygiene: no dangling pointer

    return 0;
}
