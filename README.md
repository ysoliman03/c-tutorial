# C Memory & Pointer Examples

A collection of short, self-contained C programs demonstrating common memory
bugs and core pointer concepts. Each file is independent — compile and run
whichever one you want to explore.

Files 01 and 02 also include ASCII memory-layout diagrams in their header
comments showing exactly what goes wrong byte-by-byte.

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

## Quickstart (Online, No Setup Required)

The fastest way to run any example — and the most reliable for the
overflow demos: **[onlinegdb.com](https://www.onlinegdb.com)**

1. Open onlinegdb.com
2. Make sure the language dropdown (top right) says **C**
3. Paste the contents of any `.c` file
4. Click the green **Run** button
5. For examples 02 and 03, open the gear icon → *Extra Compiler Flags* and add:
   ```
   -fno-stack-protector -O0 -Wno-error
   ```

OnlineGDB runs on Linux with an older gcc that has minimal protections, so
buffer overflows show their effects cleanly. This is actually the *recommended*
option for the overflow demos, especially if you're on a Mac.

## Running Locally

Most examples compile and run with a plain `gcc`:

```bash
gcc -o example 01_missing_terminator.c
./example
```

The trouble only starts with examples 02 and 03 — the buffer-overflow demos —
because modern compilers and operating systems have added layers of protection
specifically to stop the bug you're trying to show. You need to turn those
protections off.

### On Linux

```bash
gcc -fno-stack-protector -O0 -Wno-error -o example 02_strcpy_overflow.c
./example
```

### On macOS (important!)

macOS's `gcc` is actually Apple Clang, and it ships with aggressive runtime
checks (`_FORTIFY_SOURCE`) that will kill the program the moment it detects
an overflow. If you compile with just `-fno-stack-protector`, you'll see
something like this:

```
$ ./e2
next_var before: DATA
zsh: trace trap  ./e2
```

That "trace trap" means the `__strcpy_chk` runtime check detected the
corruption and called `abort()` — so you never get to see the corrupted
`next_var` printed. Great for production safety; useless for a teaching demo.

To disable fortify-source and see the overflow, add `-D_FORTIFY_SOURCE=0`:

```bash
gcc -fno-stack-protector -D_FORTIFY_SOURCE=0 -O0 -o example 02_strcpy_overflow.c
./example
```

If that still traps, try the nuclear option:

```bash
gcc -fno-stack-protector -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0 -O0 -fno-builtin -o example 02_strcpy_overflow.c
./example
```

For the overflow examples on macOS, it's usually easier to just use OnlineGDB.

### Compile-flag cheat sheet

| Flag | What it disables |
|------|------------------|
| `-fno-stack-protector`   | Stack canaries (the "stack smashing detected" abort) |
| `-D_FORTIFY_SOURCE=0`    | macOS/glibc runtime buffer-size checks (`__strcpy_chk` etc.) |
| `-fno-builtin`           | The compiler substituting its own safer `strcpy` implementation |
| `-O0`                    | Optimizations that can rearrange variables and hide the overflow |
| `-Wno-error`             | Treating compile-time warnings about these bugs as errors |

## Suggested Teaching Order

The examples build on each other. A good progression:

1. **01** — motivate *why* strings need `\0`
2. **02** — show what happens when you don't leave room for it (overflow)
3. **03** — show that modern alternatives (`fgets`) can still fail if misused
4. **04** — show the correct idiom
5. **05** — introduce pointers on their own, without the distraction of bugs
6. **06** — show why pointers are useful (pass-by-reference via address)
7. **07** — connect pointers back to arrays
8. **08** — dynamic allocation, where pointers become essential

## A Teaching Moment Hiding in the "Trace Trap"

If you run example 02 on a modern Mac and see `trace trap` instead of the
corruption, don't skip past it — that's a lecture in itself:

> "The program didn't even get to the corrupted `printf`. Modern operating
> systems and compilers have added layers of protection specifically because
> this bug pattern was so common and so exploitable that attackers built
> entire careers around it. We have to intentionally *disable* these
> protections just to see the bug. That's how big a deal buffer overflows
> are — and how recently they stopped being exploitable-by-default."

Then switch to OnlineGDB (or add the fortify-source flags) to actually show
the corruption.

## The Three Rules That Prevent 90% of Pointer Bugs

1. **Initialize every pointer** — to a valid address or to `NULL`.
2. **Check before you dereference** — especially after `malloc`.
3. **Match every `malloc` with exactly one `free`** — not zero (leak), not two (crash).

## A Note on Compiler Warnings

Modern `gcc` and `clang` will warn about several bugs in these examples at
compile time — for instance:

```
warning: 'strcpy' will always overflow; destination buffer has size 5,
         but the source string has length 6 (including NUL byte)
```

These warnings are a feature, not a nuisance — the compiler is literally
catching the bug before you even run the code. In real code, always compile
with `-Wall -Wextra` and take the warnings seriously.