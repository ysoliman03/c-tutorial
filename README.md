# C Memory & Pointer Examples

A collection of short, self-contained C programs demonstrating common memory
bugs and core pointer concepts. Each file is independent — compile and run
whichever one you want to explore.

## The Examples

| # | File | Concept |
|---|------|---------|
| 01 | `01_missing_terminator.c` | A string without `\0` prints garbage beyond its intended end |
| 02 | `02_strcpy_overflow.c`    | `strcpy` has no size check and silently corrupts neighboring memory |
| 03 | `03_fgets_wrong_size.c`   | `fgets` is only safe when the size parameter is honest |
| 04 | `04_fgets_correct.c`      | The safe idiom: `fgets(buf, sizeof(buf), stdin)` |
| 05 | `05_pointer_basics.c`     | `&` (address-of) and `*` (dereference) |
| 06 | `06_swap_with_pointers.c` | Why pointers exist: modifying caller's variables |
| 07 | `07_array_pointer_decay.c`| Arrays are secretly pointers; `arr[i]` is `*(arr + i)` |
| 08 | `08_malloc_basics.c`      | Requesting memory at runtime with `malloc` and releasing it with `free` |

## How to Run (Locally)

Compile any file with `gcc`:

```bash
gcc -o example 01_missing_terminator.c
./example
```

For the buffer-overflow examples (02, 03), disable stack protection so the
corruption is visible instead of being caught and aborted:

```bash
gcc -fno-stack-protector -O0 -Wno-error -o example 02_strcpy_overflow.c
./example
```

## How to Run (Online, No Setup)

The easiest option for students: **[onlinegdb.com](https://www.onlinegdb.com)**

1. Open onlinegdb.com
2. Make sure the language dropdown says **C**
3. Paste the contents of any `.c` file
4. Click the green **Run** button
5. For examples 02–03, open the gear icon and add to *Extra Compiler Flags*:
   ```
   -fno-stack-protector -O0 -Wno-error
   ```


## The Three Rules That Prevent 90% of Pointer Bugs

1. **Initialize every pointer** — to a valid address or to `NULL`.
2. **Check before you dereference** — especially after `malloc`.
3. **Match every `malloc` with exactly one `free`** — not zero (leak), not two (crash).

## A Note on Compiler Warnings

Modern `gcc` will warn about several bugs in these examples at compile time
(e.g., `'fgets' writing 32 bytes into a region of size 8`). These warnings
are a feature, not a nuisance — they're the compiler doing its best to save
you from yourself. Always compile with `-Wall -Wextra` in real code.
