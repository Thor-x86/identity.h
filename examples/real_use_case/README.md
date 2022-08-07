# Use Case: Identify Plugin's Role

This example demonstrate one of use-case for `identity.h`. Main program is `executable.c` and will be compiled to `real_use_case` executable file. That executable loads plugin to do different behaviors for each plugin combinations. It accepts 3 roles of plugin as graph below.

```
||============|| Message ||==============|| Message ||=============||
|| Input Node || ======> || Process Node || ======> || Output Node ||====||
||============||         ||==============||         ||=============||    ||
       /\                                                                ||
       || Message or NULL                                                ||
       ||================================================================||
```

As a user, you can interchange plugins for each role, but each role **must exactly** filled by one plugin.

> DISCLAIMER: In this example, author assumes you're using UNIX-like operating system. Thus, this won't work on Windows.

## Build Instruction

First of all, you **need** to use [clang compiler](https://clang.llvm.org/get_started.html) because GCC has trouble assigning `IDENTITY` and `IDENTITY_INT` to `enum` and `switch-case`. Also make sure you did **build and install identity.h** before and has [GNU Make](https://www.gnu.org/software/make/) program installed. After everything's ready, you can simply run this command:

```bash
make
```

## Usage Instruction

If you run this:

```bash
./real_use_case
```

Then it will show the quick guide and example:

```
USAGE:
    ./real_use_case <input plugin> <process plugin> <output plugin>

EXAMPLE:
    ./real_use_case ./input-terminal.so ./process-toggle_case.so ./output-terminal.so
```

...or this, for Mac users:

```
EXAMPLE:
    ./real_use_case ./input-terminal.dylib ./process-toggle_case.dylib ./output-terminal.dylib
```

## More Usage Examples

### Linux-Based Platform

```bash
./real_use_case ./input-terminal.so ./process-toggle_case.so ./output-terminal.so
```

```bash
./real_use_case ./input-terminal.so ./process-reverse.so ./output-terminal.so
```

```bash
./real_use_case ./input-file.so ./process-toggle_case.so ./output-terminal.so
```

```bash
./real_use_case ./input-repeat.so ./process-roll.so ./output-terminal.so
```

### MacOS

```zsh
./real_use_case ./input-terminal.dylib ./process-toggle_case.dylib ./output-terminal.dylib
```

```zsh
./real_use_case ./input-terminal.dylib ./process-reverse.dylib ./output-terminal.dylib
```

```zsh
./real_use_case ./input-file.dylib ./process-toggle_case.dylib ./output-terminal.dylib
```

```zsh
./real_use_case ./input-repeat.dylib ./process-roll.dylib ./output-terminal.dylib
```
