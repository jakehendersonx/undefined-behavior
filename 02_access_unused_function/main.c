
// Compile with
//
// gcc-15 -O0 \
//        -fno-strict-aliasing \
//        -fwrapv \
//        -fno-delete-null-pointer-checks \
//        -fno-strict-overflow \
//        -std=gnu99 \
//        --sysroot=$(xcrun --show-sdk-path) \
//        -fno-stack-protector \
//        -fno-omit-frame-pointer \
//        -no-pie \
//        main.c -o main.exe
//
// ./main.exe

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void secret_function(void) {
    printf("=== SECRET FUNCTION EXECUTED! ===\n");
    printf("Hidden ACE-like payload ran via stack overflow UB.\n");
    printf("This only happens because of the memory corruption.\n");
    exit(0); // no legit return address on the stack, so bail cleanly
}

void vulnerable_function(char *input) {
    char buffer[16];
    memcpy(buffer, input, 32); // UB buffer overflow (memcpy to survive null bytes)
    printf("Buffer filled. Normal path continues...\n");
}

int main(void) {
    printf("=== Simple ACE Demo (hidden via UB on arm64) ===\n\n");

    // Padding tuned for GCC -O0 on Apple Silicon (overwrites caller's saved LR)
    // 16 bytes fills buffer, +8 overwrites main's saved x29, then x30
    char payload[80] = {0};
    memset(payload, 'A', 24);

    uintptr_t secret_addr = (uintptr_t)secret_function;
    memcpy(payload + 24, &secret_addr, sizeof(secret_addr));

    printf("Attempting overflow with 24-byte padding...\n");
    vulnerable_function(payload);

    printf("Back in main().\n");
    return 0;
}
