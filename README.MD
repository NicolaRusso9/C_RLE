## Overview & Project Purpose
This project implements a lightweight, high-reliability command-line file compression and decompression tool developed in C.

This tool automates the reduction and restoration of large text files containing critical information. In environments where system resources (RAM, processing power, disk space) are heavily constrained, standard heavy compression libraries (like `gzip` or `zlib`) introduce unwanted overhead. This tool provides a minimalist, zero-dependency alternative optimized for minimal memory usage and deterministic execution.

## Key Features

- **Resource-Aware Memory Management:** Accepts arbitrary and extra-long file paths without path truncation or fixed-buffer. Memory is allocated on-demand and freed immediately.
- **Run-Length Encoding (RLE) Algorithm:** Implements an adapted RLE algorithm:
    - Sequences of repeating characters are compressed into `<character><count>` format (e.g., `aaaa` $\rightarrow$ `a4`).
    - Linebreak characters (`\n`, `\r`) are preserved as-is without breaking sequence logic or adding artificial counts.
- **Non-Destructive File Versioning:** Prevents accidental data destruction. If an output target already exists on disk, the tool automatically resolves path collisions by appending version suffixes (`_1`, `_2`, etc.).
- **Robust Error Handling:** Features complete stream verification, gracefully reporting I/O errors and corrupted inputs with standardized exit status codes.

## Lightweight Design Considerations

While highly efficient for text files with high repetition, this tool is intentionally a **lightweight/specialized implementation**:

1. **Algorithm Simplicity:** RLE targets consecutive character runs.
2. **ASCII / Byte-Oriented:** The tool processes characters byte-by-byte.
3. **Stream Processing:** Designed to process files incrementally via streams, keeping memory footprint practically static regardless of input file size.

---

## Project Structure

```text
.
├── CMakeLists            # For automation building with CMake
├── README.md             # Project documentation
├── test_files/           # Simple file to test algorithm
│   ├── test.rls          # Compressed file
│   └── test.txt          # File to compress
├── header_files/         # Modular C header definitions
│   ├── compress.h
│   ├── constants.h
│   ├── decompress.h
│   └── utils.h
└── src/                  # Source implementation files
    ├── compress.c
    ├── constants.c
    ├── decompress.c
    ├── main.c
    └── utils.c
```

## CMake Building

#### Compile the tool using `CMakeLists.txt`

Open Terminal into root of project:
```
C_Compressor/
├── CMakeLists.txt
├── src/
└── header_files/
```

Configure and build project with make:
```bash
rm -rf build
mkdir build
cd build
cmake ..
make
```


## Manual Building and Execution
Compile and build command:

```bash 
cd src
gcc -Wall -Wextra -std=c11 main.c compress.c decompress.c constant.c utils.c -o starter
```

Can execute program with command:
```
./src/starter FLAG FILE_PATH
```

ex.:
```bash
./src/starter -d ../test_files/test.rle
```
