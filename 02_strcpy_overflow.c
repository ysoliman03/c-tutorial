/*
 * Example 02: strcpy Buffer Overflow
 * ----------------------------------
 * strcpy does NOT check the destination size. It copies until it hits '\0'
 * in the source. Writing "hello" (5 chars + '\0' = 6 bytes) into a 5-byte
 * array overflows by one byte into whatever sits next in memory.
 *
 * Expected output (may vary by compiler):
 *   next_var before: DATA
 *   s:               hello
 *   next_var after:
 *
 * The '\0' from strcpy landed on next_var[0], turning 'D' into '\0' -- so
 * next_var now looks empty, even though 'A', 'T', 'A' are still sitting in
 * next_var[1..3].
 *
 * Memory layout after the strcpy:
 *
 *   [ s[0] ][ s[1] ][ s[2] ][ s[3] ][ s[4] ][ next_var[0] ][ next_var[1] ]...[ next_var[7] ]
 *     'h'     'e'     'l'     'l'     'o'       '\0'            'A'              '\0'
 *                                                 ^
 *                                       strcpy wrote '\0' here!
 *
 * The 6th byte of "hello" had nowhere to go inside s[], so it spilled into
 * next_var[0] and silently overwrote the 'D'. printf("%s", next_var) now
 * hits a '\0' immediately and prints nothing.
 *
 * Compile with: gcc -fno-stack-protector -O0 -o 02 02_strcpy_overflow.c
 * (stack protection can mask or abort this kind of overflow)
 */

#include <stdio.h>
#include <string.h>

int main(void) {
    char next_var[8] = "DATA";
    char s[5];                        // only 5 slots -- no room for '\0'!

    printf("next_var before: %s\n", next_var);

    strcpy(s, "hello");               // 6 bytes written into a 5-byte array

    printf("s:               %s\n", s);
    printf("next_var after:  %s\n", next_var);   // corrupted!

    // Proof that the original bytes are still there, just unreachable:
    printf("\nProof next_var still holds the bytes:\n");
    printf("  next_var[0] = %d (the \\0 that overwrote 'D')\n", next_var[0]);
    printf("  next_var[1] = %c\n", next_var[1]);
    printf("  next_var[2] = %c\n", next_var[2]);
    printf("  next_var[3] = %c\n", next_var[3]);

    return 0;
}
