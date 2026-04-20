/*
 * Example 07: Arrays Are Secretly Pointers
 * 
 * When you use an array name without brackets, it "decays" into a pointer
 * to its first element. This is why arr[i] and *(arr + i) are identical,
 * and why functions that take arrays actually take pointers.
 *
 * Expected output:
 *   nums[0]:   10
 *   *nums:     10
 *   *(nums+0): 10
 *   nums[2]:   30
 *   *(nums+2): 30
 *   Array contents: 10 20 30 40 50
 *
 * Key insight: arr[i] is literally shorthand for *(arr + i).
 * This is also WHY string comparison with == doesn't work --
 * it would compare addresses, not contents.
 */

#include <stdio.h>

void print_array(int *arr, int size) {
    printf("Array contents: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);       // bracket notation works on pointers!
    }
    printf("\n");
}

int main(void) {
    int nums[5] = {10, 20, 30, 40, 50};

    // These three are ALL the same thing:
    printf("nums[0]:   %d\n", nums[0]);
    printf("*nums:     %d\n", *nums);        // nums decays to a pointer
    printf("*(nums+0): %d\n", *(nums + 0));  // pointer arithmetic

    // nums[2] is literally *(nums + 2)
    printf("nums[2]:   %d\n", nums[2]);
    printf("*(nums+2): %d\n", *(nums + 2));  // same thing

    print_array(nums, 5);   // pass the array (decays to pointer)
    return 0;
}
