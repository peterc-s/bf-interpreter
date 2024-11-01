# bf-interpreter
An interpreter for the Brainfuck language, written in C.

## Features
- Dynamic memory allocation of data cells.
- Allows source files up to 128MB! (Can be altered in source code.)

## Building
```bash
git clone https://github.com/peterc-s/bf-interpreter
```

### With Zig
Make sure you have the Zig toolchain installed and that the latest commit does not
have a WIP tag.

```bash
zig build
```

Will build the binary and put it into `zig-out/bin/`.

### With Make
Make sure you have GCC.

```bash
make
```

Will build the binary to the project root directory as `bf-interpreter`.

To build and run with args:
```bash
make run ARGS="bf-examples/fib.bf"
```

To clean up build artifacts:
```bash
make clean
```

## TODO
- More robust error handling with better error messaging.
- Find a better way to free before exiting (best practice).
- Tests.
