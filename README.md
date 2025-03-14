# CS110

## proj
### proj 1.1
Implement a basic RISC-V assembler that converts assembly instructions into machine code. This implementation will support the .data segment of assembly files and focus specifically on the RV32I instruction set along with partial RV32M extensions.

The assembler operates in two phases:

- Phase 1: Parse the assembly source (.S file), remove comments, populate a symbol table with labels, and generate an intermediate representation containing basic instructions and expanded pseudo-instructions.
- Phase 2: Using the symbol table and intermediate representation, translate each instruction into its corresponding machine code (binary representation) and output the result in hexadecimal format.
