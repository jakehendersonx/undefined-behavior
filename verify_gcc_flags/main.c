#include <stdint.h>
#include <stdio.h>

int main(void) {
    // Strict aliasing violation example (type punning)
    float f = 3.14159f;
    uint32_t *ip = (uint32_t *)&f; // This is UB under strict aliasing

    printf("Float as bits (raw): 0x%08x\n", *ip);

    // Modify via the int pointer — should change the float bits
    *ip = 0x40490fdb; // This is approximately pi in IEEE 754 single precision

    printf("After writing bits via int*: %f (should still be ~pi)\n", f);

    // Signed overflow test (wraparound behavior)
    int x = 2147483647; // INT_MAX on 32-bit int
    x = x + 1;
    printf("Signed overflow: %d (with -fwrapv should be -2147483648)\n", x);

    return 0;
}
