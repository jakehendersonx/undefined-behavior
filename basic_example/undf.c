#include <limits.h>
#include <stdio.h>

/**
 * Compiler forcing wrapping causes two added positive
 * ints to be negative in output.
 *
 * clang -std=c99 -O2 -fwrapv -o undf.exe undf.c && ./undf.exe
 */
int main(void) {
  volatile int a = INT_MAX;
  volatile int b = 1;

  if (a > 0 && b > 0) {
    int sum = a + b;
    if (sum <= 0)
      printf("IMPOSSIBLE: positive + positive = negative?!\n");
    else
      printf("sum = %d\n", sum);
  }
  return 0;
}
