/*
 * Example 04: fgets done CORRECTLY with sizeof()
 * 
 * Using sizeof(name) guarantees the size parameter matches the array,
 * even if you later resize the array. fgets will then safely truncate
 * oversized input instead of overflowing.
 *
 * Try entering:  AAAAAAAAAAAAAAAAAAAA   (20 A's)
 *
 * Expected output:
 *   Secret before: SECRET
 *   Enter your name: AAAAAAAAAAAAAAAAAAAA
 *   Hello, AAAAAAA           <-- only 7 chars read + '\0'
 *   Secret after:  SECRET    <-- still intact!
 *
 * The extra A's stay in the input buffer (harmlessly discarded if no
 * further reads). The neighboring 'secret' variable is never touched.
 */

#include <stdio.h>

int main(void) {
    char secret[8] = "SECRET";
    char name[8];

    printf("Secret before: %s\n", secret);
    printf("Enter your name: ");

    // CORRECT: sizeof(name) is always accurate
    fgets(name, sizeof(name), stdin);

    printf("Hello, %s", name);
    printf("Secret after:  %s\n", secret);

    return 0;
}
