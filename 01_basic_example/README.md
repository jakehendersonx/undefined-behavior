# UB-Friendly GCC for Self-Replicating Genetic Algorithm

This project relies on a permissive GCC setup to allow classic undefined behavior tricks (strict aliasing violations, signed overflow wraparound, type punning, etc.). These behaviors are heavily optimized away by modern Clang on Apple Silicon, but survive with the right GCC flags.

### 1. Fix / Install GCC on macOS (Apple Silicon)

If you see `stdint.h: No such file or directory` or similar header errors:

````bash
# Reinstall Xcode Command Line Tools
xcode-select --install

# Full reinstall of GCC
brew uninstall gcc
brew install gcc

# Verify installation
gcc-15 --version

```bash
gcc-15 -O0 \
       -fno-strict-aliasing \
       -fwrapv \
       -fno-delete-null-pointer-checks \
       -fno-strict-overflow \
       -std=gnu99 \
       --sysroot=$(xcrun --show-sdk-path) \
       main.c -o main.exe

````

running `./main.exe` should yeild a signed overflow.

```bash
Float as bits (raw): 0x40490fd0
After writing bits via int*: 3.141593 (should still be ~pi)
Signed overflow: -2147483648 (with -fwrapv should be -2147483648)
```
