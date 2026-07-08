# *This project has been created as part of the 42 curriculum by <thamoliv>.*

# get_next_line

## Description

The goal of this project is to implement the function `get_next_line`, capable of reading a file descriptor line by line.

Unlike standard file reading functions, `get_next_line` preserves unread data between function calls using a static variable. This allows the function to return one complete line at a time without rereading previously processed data.

The returned string always includes the terminating newline character (`\n`) when it exists. If the end of the file is reached without a trailing newline, the last line is returned without `\n`. When there is nothing left to read or an error occurs, the function returns `NULL`.

---

## Files

* `get_next_line.c` — main function and line extraction.
* `get_next_line_utils.c` — helper functions for string handling, reading, and buffer management.
* `get_next_line.h` — prototypes and `BUFFER_SIZE` definition.

---

## Algorithm

The algorithm is based on maintaining a static string called `saved`.

### Step 1

When `get_next_line()` is called, the function first checks whether `saved` already contains a newline.

If it does not, additional data is read from the file using `read()`.

---

### Step 2

Each new chunk read from the file is concatenated to `saved`.

Reading continues until:

* a newline is found; or
* the end of the file is reached.

---

### Step 3

Once a complete line is available, the function extracts it.

If a newline exists, the returned string contains everything from the beginning of `saved` through the newline.

Otherwise, the entire remaining content is returned.

---

### Step 4

After returning the line, the already processed characters are removed from `saved`.

Only the unread part of the file remains stored for the next call.

---

### Step 5

Subsequent calls repeat the same process until no data remains.

When both the file and `saved` are empty, the function returns `NULL`.

---

## Why use a static variable?

A normal local variable is destroyed when the function returns.

Since `get_next_line()` is called multiple times, it must remember the unread characters between calls.

A static variable is created only once and keeps its value throughout the entire execution of the program, making it ideal for storing the remaining data.

---

## Memory Management

The implementation dynamically allocates memory for:

* the temporary read buffer;
* concatenated strings;
* the returned line;
* the remaining unread content.

Every obsolete allocation is freed before replacement to prevent memory leaks.

---

## Compilation

Default compilation:

```bash
cc -Wall -Wextra -Werror *.c
```

Using a custom buffer size:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 *.c
```

Any positive value may be used for `BUFFER_SIZE`.

---

## Example

Input file:

```
Hello
42
School
```

Calls:

```c
get_next_line(fd); // "Hello\n"
get_next_line(fd); // "42\n"
get_next_line(fd); // "School"
get_next_line(fd); // NULL
```

---

## Resources

* Linux manual
* The C Programming Language — Brian Kernighan & Dennis Ritchie
* 42 subject documentation
* cppreference.com (general C reference)

### AI Usage

Artificial intelligence was used as a learning assistant to clarify C concepts, review the implementation, improve code readability, prepare documentation, and help understand the algorithm. The implementation, debugging, and final validation were completed manually.
