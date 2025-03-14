# CS110

## proj
### proj 1.1
Implement a basic RISC-V assembler that converts assembly instructions into machine code. This implementation will support the .data segment of assembly files and focus specifically on the RV32I instruction set along with partial RV32M extensions.

The assembler operates in two phases:

- Phase 1: Parse the assembly source (.S file), remove comments, populate a symbol table with labels, and generate an intermediate representation containing basic instructions and expanded pseudo-instructions.
- Phase 2: Using the symbol table and intermediate representation, translate each instruction into its corresponding machine code (binary representation) and output the result in hexadecimal format.

## hw
### hw2
Implement parsing of a modified floating-point format ca25 and conversion from the format to IEEE 754 single-precision floating-point number (fp32).

The C program keep performing the following tasks until EOF is met:

- Read a ca25 floating-point number which is expressed in 16-digit hex.
- Convert the loaded ca25 number to single-precision fp32.

For each ca25 number, the program produces three lines of output:

- Print the sign, exponent and significand of the original ca25.
- Print the sign, exponent and significand of the converted fp32.
- Print the hex representation of the converted fp32.
