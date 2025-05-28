# CS110

Computer Architecture is mandatory for all Computer Science majors. It teaches the internal organization and operation of digital computers. The class covers C and assembly language programming, memory management, how higher-level programs are translated into machine language, computer organization, computer logic and CPU design, caches, performance measurement, parallelism, warehouse scale computing, and related topics.

## Project

### RISC-V to Machine Code converter

[code](https://github.com/AristurtleHu/RISC-V_to_MC_converter)

Implement a basic RISC-V assembler that converts assembly instructions into machine code.

### MD5 in RISC-V
[code](https://github.com/AristurtleHu/MD5_in_RISC-V)

Implement the MD5 cryptographic hash algorithm using the RISC-V instruction set (using assembly language)

###  Single-Cycle CPU of RISC-V
[code](https://github.com/AristurtleHu/Single-Cycle_CPU_of_RISC-V)

Implement a single-cycle CPU which can process basic instructions of RISC-V

### 5-Stage Pipelined Toy CPU
[code](https://github.com/AristurtleHu/5-Stage-Pipelined-Toy-CPU)

Implement a 5-stage pipelined CPU which can process all the instructions from Project 2.1 (solving Structural, Data and Control Hazards)

### Encrypt and Hash
[code](https://github.com/AristurtleHu/Encrypt-and-Hash)

Use all knowledge about computer architecture to optimize a program with encryption and hashing. Modify the code to improve its time performance. (Cache Blocking, SIMD, Loop Unrolling, Multithreading) 

### Shooting Game
[code](https://github.com/AristurtleHu/Shooting-Game)

Use C language and RISC-V assembly to implement a STG (Shooting Game). Also use PlatformIO to cross-compile and generate a program for the Longan Nano development board.

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

### HW4

Questions about:
- Combinational logic
- SDS
- FSM

### HW5

Questions about:
- Set-Associative Caches
- AMAT
- Hit Rate

### HW6

Implement a simplified RISC-V simulator and a single-level unified cache to observe performance issues related to shared instruction/data caches.

Run by `make && ./main <assembly code to run> 2>main.log`

- Part 1: RISC-V Simulator
  - Implement a simulator for a subset of RISC-V instructions.
  - Maintain 32 integer registers and the Program Counter (PC).
  - Parse and execute assembly code sequentially, assuming instructions start at address 0x0.
  - Handle `lw`/`sw` by calculating addresses only (no actual memory load/store).
  - Handle `li` by loading the immediate directly (no pseudo-instruction expansion).

- Part 2: Unified Cache Simulator
  - Implement a unified cache shared by instructions and data.
  - Specifications: Write-allocate, 16-byte block size, 4 blocks, Fully Associative, LRU replacement.
  - Track total memory accesses, instruction cache hits, data cache hits, and total cache misses.
  - Simulate cache behavior for instruction fetches and `lw`/`sw` data accesses.
  - Print the final counts for total memory accesses, instruction hits, data hits, and total misses.

### HW7

Questions about:
- TLB
- Multi-level Page Tables 
- Page Faults
- Page Table Walk

### HW8

Questions about:

- Basic Concepts
- Number Representation
- Logic
- FSM
- C, Risc-V and Cache
- Pipeline
- AMAT and Performance