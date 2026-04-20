/*
 * Example 05: Pointer Basics
 * 
 * A pointer is a variable that stores an ADDRESS instead of a value.
 * The two essential operators:
 *   &x   "address-of"  -> where does x live?
 *   *p   "dereference" -> what's stored at the address in p?
 *
 * Expected output:
 *   Value of x:           5
 *   Address of x:         0x7ffe...  (some hex address)
 *   Value stored in ptr:  0x7ffe...  (same address)
 *   Value ptr points to:  5
 *   x is now:             99
 *
 * Key insight: *ptr = 99 and x = 99 do the SAME thing.
 * The pointer is just a second handle on the same memory.
 */

#include <stdio.h>

int main(void) {
    int x = 5;
    int *ptr;        // declare a pointer to an int

    ptr = &x;        // store the ADDRESS of x in ptr

    printf("Value of x:           %d\n", x);       // 5
    printf("Address of x:         %p\n", (void*)&x);
    printf("Value stored in ptr:  %p\n", (void*)ptr);   // same address
    printf("Value ptr points to:  %d\n", *ptr);    // 5 (dereferenced)

    *ptr = 99;       // change x THROUGH the pointer
    printf("x is now:             %d\n", x);       // 99

    return 0;
}
