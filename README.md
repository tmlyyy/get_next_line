*This project has been created as part of the 42 curriculum by < thamoliv >.*

# get_next_line

## Description

The goal of this project is to implement the function `get_next_line`, capable of reading a file descriptor line by line.

Unlike standard file reading functions, `get_next_line` preserves unread data between function calls using a static variable. This allows the function to return one complete line at a time without rereading previously processed data.

The returned string always includes the terminating newline character (`\n`) when it exists. If the end of the file is reached without a trailing newline, the last line is returned without `\n`. When there is nothing left to read or an error occurs, the function returns `NULL`.

**Bonus Features:** The bonus implementation takes this a step further by managing multiple file descriptors simultaneously, using only a single static variable (an array of pointers). This allows interleaved reading from different files without losing their respective reading states.

---

## Files

**Mandatory Part:**
* `get_next_line.c` — main function and line extraction.
* `get_next_line_utils.c` — helper functions for string handling, reading, and buffer management.
* `get_next_line.h` — prototypes and `BUFFER_SIZE` definition.

**Bonus Part:**
* `get_next_line_bonus.c` — main function updated to support multiple FDs using an array.
* `get_next_line_utils_bonus.c` — refactored helper functions to work without an explicit length variable.
* `get_next_line_bonus.h` — prototypes, `BUFFER_SIZE`, and `MAX_FD` definition.

---

## Algorithm & Technical Choices

The algorithm is based on maintaining a static string called `saved` (or an array of strings for the bonus part).

### Why use a static variable?
A normal local variable is destroyed when the function returns. Since `get_next_line()` is called multiple times, it must remember the unread characters between calls. A static variable is created only once and keeps its value throughout the entire execution of the program, making it ideal for storing the remaining data.

### The Bonus Approach: Managing Multiple FDs
To handle multiple file descriptors concurrently while adhering to the rule of using only **one** static variable, an array of static pointers is used: `static char *saved[MAX_FD];`. Since file descriptors are simply integer values, the `fd` itself acts as the exact index for the array. For instance, any remainder text read from `fd 3` is stored directly in `saved[3]`, isolating its state from `fd 4` stored in `saved[4]`.

### Step-by-Step Execution
1. **Validation & Initialization:** Check if `fd` is valid and within limits.
2. **Read and Accumulate:** If the `saved[fd]` string doesn't contain a newline (`\n`), additional data is read using `read()` in chunks defined by `BUFFER_SIZE`. Each chunk is concatenated to `saved[fd]` until a newline is found or the end of the file is reached.
3. **Extract Line:** Once a complete line is available (up to the first `\n`), it is extracted and dynamically allocated to the `line` variable.
4. **Extract Rest:** The remaining characters *after* the newline are duplicated into a new string. The old `saved[fd]` is freed to prevent memory leaks, and the pointer is updated to point to this new "remainder" string.
5. **Return:** The extracted line is returned to the caller. When both the file and `saved` are empty, the function cleans up and returns `NULL`.

---

## Memory Management

The implementation dynamically allocates memory for:
* the temporary read buffer;
* concatenated strings;
* the returned line;
* the remaining unread content.

Every obsolete allocation is meticulously freed before replacement to prevent memory leaks.

---

## Compilation & Testing

Default compilation (Mandatory):
```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c
./a.out teste.txt

```

Default compilation (Bonus):

```bash
cc -Wall -Wextra -Werror get_next_line_bonus.c get_next_line_utils_bonus.c main_bonus.c
./a.out teste.txt teste2.txt

```

Using a custom buffer size:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main_bonus.c
./a.out teste.txt teste2.txt

```
Note: You can change BUFFER_SIZE to any positive integer (e.g., 1, 10, 9999) to test how the function handles different read chunks.

---

## Resources

* Linux manual (`man 2 read`, `man 3 malloc`, `man 3 free`)
* The C Programming Language — Brian Kernighan & Dennis Ritchie
* 42 subject documentation
* cppreference.com (general C reference)

### AI Usage

Artificial intelligence tools (Claude and Gemini) were used as learning assistants to clarify C concepts, review the implementation, improve code readability, prepare documentation, and help understand the algorithm. AI also provided guidance on structuring the single static array approach for the bonus implementation. The implementation, debugging, refactoring, and final validation were completed manually.
