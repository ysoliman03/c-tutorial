/*
 * Example 01: Missing Null Terminator
 * 
 * strncpy copies exactly N characters but does NOT add '\0' if the source
 * is exactly N chars or longer. Without a terminator, printf keeps reading
 * memory until it finds one by accident.
 *
 * Expected output:
 *   Before: long string
 *   After:  shortstring   <-- BUG: we wanted just "short"
 *
 * Why: s[0..4] now holds 'short', but s[5..10] still holds the leftover
 * 'string' from before, and there's no '\0' between them.
 */

#include <stdio.h>
#include <string.h>

int main(void) {
    char s[12] = "long string";   // 11 chars + '\0' at s[11]

    printf("Before: %s\n", s);

    strncpy(s, "short", 5);       // copies 5 chars, does NOT append '\0'

    printf("After:  %s\n", s);    // prints "shortstring" -- the bug!

    return 0;
}
