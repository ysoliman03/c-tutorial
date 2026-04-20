/*
 * Example 03: fgets with the WRONG size (the book's warning)
 * 
 * fgets is only safe if you pass it the correct array size. Here we lie
 * to fgets and tell it the array is 32 bytes when it's actually 8.
 * fgets trusts us -- and overflows the buffer into 'secret'.
 *
 * Try entering:  AAAAAAAAAAAAAAAAAAAA   (20 A's)
 *
 * Expected output:
 *   Secret before: SECRET
 *   Enter your name: AAAAAAAAAAAAAAAAAAAA
 *   Hello, AAAAAAAAAAAAAAAAAAAA
 *   Secret after:  AAAAAAAAAAAA   <-- corrupted!
 *
 * Modern GCC will warn about this at compile time with:
 *   warning: 'fgets' writing 32 bytes into a region of size 8
 *
 * Compile with: gcc -fno-stack-protector -O0 -Wno-error -o 03 03_fgets_wrong_size.c
 */

#include <stdio.h>

int main(void) {
    char secret[8] = "SECRET";
    char name[8];

    printf("Secret before: %s\n", secret);
    printf("Enter your name: ");

    // LIE: array is 8, but we told fgets it's 32
    fgets(name, 32, stdin);

    printf("Hello, %s", name);
    printf("Secret after:  %s\n", secret);

    return 0;
}
