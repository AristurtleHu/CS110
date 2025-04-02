# CS110

## Project

### 1.1

[code](https://github.com/AristurtleHu/RISC-V_to_MC_converter)

Implement a basic RISC-V assembler that converts assembly instructions into machine code.

### 1.2
[code](https://github.com/AristurtleHu/MD5_in_RISC-V)

Implement the MD5 cryptographic hash algorithm using the RISC-V instruction set (using assembly language)

## HW

### HW2

Implement parsing of a modified floating-point format ca25 and conversion from the format to IEEE 754 single-precision floating-point number (fp32).

The C program keep performing the following tasks until EOF is met:

- Read a ca25 floating-point number which is expressed in 16-digit hex.
- Convert the loaded ca25 number to single-precision fp32.

For each ca25 number, the program produces three lines of output:

- Print the sign, exponent and significand of the original ca25.
- Print the sign, exponent and significand of the converted fp32.
- Print the hex representation of the converted fp32.

### HW3

Implement an efficient leaderboard system composed of two complementary data structures:

- Skip List: Provides efficient sorted access by score and rank lookups
- Hash Map: Provides fast lookups by member name

The Skip List maintains a mapping from score to member (allowing for rank-based operations), while the Hash Map maintains a mapping from member to score (enabling quick score lookups). Together, they provide optimal performance for all leaderboard operations.