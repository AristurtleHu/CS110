// #set text(font: "Maple Mono Normal NL NF")
#import "hw5-sol.typ": t1, t2-1, t2-2, t2-3, t3-1, t3-2, t3-3, t4-1, t4-2

#set text(font: "New Computer Modern")
#set table(inset: (x: 0.5cm, y: 0.3cm), align: center + horizon)
#set page(numbering: "1")
#show raw: set text(font: "Maple Mono Normal NL NF")
// #show raw: set text(font: "Maple Mono NL NF")

#let TYPST = {
  text(font: "Linux Libertine", weight: "semibold", fill: eastern)[typst]
}

#align(center)[= CS110 sp25 HW5]
#v(1cm)
#align(center)[Due: TBD]

Complete this homework either by writing neatly by hand or using #TYPST. You can find the `.typ` file on Piazza.

#v(0.5cm)

#smallcaps[== 1 ~ True or False]\
#[
  Fill in your answer (T or F) in the table below.

  + When the same address is accessed multiple times using a cache, it primarily benefits from spatial locality.
  + If a cache system changes from direct-mapped to N-way set-associative ($N>1$), the number of `index` bits in the address breakdown increases.
  + Higher cache associativity decreases hit time, miss rate, and miss penalty simultaneously.
  + Assume a direct-mapped cache with 8-byte blocks, 2 sets, using LRU replacement, and initially empty. Given 8-bit addresses, accessing addresses from `0x00` to `0xFF` sequentially will result in no cache hits.
  #figure(
    table(
      columns: 4,
      [1], [2], [3], [4],
      ..t1
    ),
  )
]

#v(0.5cm)

#smallcaps[== 2 ~ Set-Associative Caches]\
#[
  // Consider
  Assume a 12-bit address space. All cache lines are shown in the table below.

  #figure(
    table(
      columns: (auto, 4cm, 4cm),
      [Set index], [Tag 1], [Tag 2],
      [0], [], [],
      [1], [], [],
      [2], [], [],
      [3], [], [],
    ),
  )
  // Consider a direct-mapped cache with 16 lines, each line has 32 bytes. The cache is initially empty. The following sequence of memory addresses (in decimal) are accessed: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9.
  + Assume loading a 16-byte struct at address `0x00F` requires only 1 cache lookup, but loading one at `0x011` requires 2 lookups. Fill in the cache system parameters in the table below.
    #figure(
      table(
        columns: (auto, 6cm),
        [Cache block size], t2-1.at(0),
        [Total Capacity], t2-1.at(1),
        [Level of set associativity], t2-1.at(2),
        [\# of cache blocks], t2-1.at(3),
        [\# of sets], t2-1.at(4),
        [Address Breakdown \ `(Tag | Index | Offset)`], t2-1.at(5),
      ),
    )

  + For the sequence of addresses below, indicate whether each access results in a hit, miss, or replacement. Assume the cache is initially empty.
    #figure(
      table(
        columns: 2,
        [Address], [Cache Access Result (Hit/Miss/Replacement)],
        [`0x3A8`], t2-2.at(0),
        [`0x1A6`], t2-2.at(1),
        [`0x04C`], t2-2.at(2),
        [`0x5AD`], t2-2.at(3),
        [`0x3B9`], t2-2.at(4),
        [`0x44F`], t2-2.at(5),
        [`0x1B3`], t2-2.at(6),
        [`0x055`], t2-2.at(7),
        [`0x241`], t2-2.at(8),
        [`0x45E`], t2-2.at(9),
        [`0x1A1`], t2-2.at(10),
        [`0x1A5`], t2-2.at(11),
        [`0x642`], t2-2.at(12),
        [`0x444`], t2-2.at(13),
      ),
    )

  + Calculate the cache hit rate for the sequence of memory accesses above. How can you improve the cache hit rate without increasing the cache *capacity*?
    #t2-3
]

#smallcaps[== 3 ~ AMAT]\
#[
  Consider a 3-level cache system with the following parameters, where the CPU runs at 4GHz:
  #figure(
    table(
      columns: 3,
      [Cache Level], [Hit Time], [Local Miss Rate],
      [L1], [2 cycles], [8%],
      [L2], [12 cycles], [35%],
      [L3], [44 cycles], [10%],
      [Memory], [80ns], [-],
    ),
  )

  + Calculate the global miss rate for the 3-level cache.
    #t3-1

  + Calculate the average memory access time (AMAT) for the CPU.
    #t3-2

  + Now, suppose the L1 cache is changed from 2-way set-associative to fully associative. This change reduces the L1 local miss rate to *6%* but increases the L1 hit time by *60%*. Calculate the new AMAT.
    #t3-3
]

#smallcaps[== 4 ~ Code analysis]\
#[
  Consider the following code:

  #box[
    ```c
    struct body {
        float x, y, z, r;
    };

    struct body bodies[64];

    // check whether two physics bodies overlap in 3D space
    bool is_collide(struct body a, struct body b);

    int check_collision() {
        int count = 0;
        for (int i = 0; i < 64; i++) {
            for (int j = i + 1; j < 64; j++) {
                if (is_collide(bodies[i], bodies[j])) {
                    count++;
                }
            }
        }
        return count;
    }
    ```
  ]

  Note:
  - Assume the cache parameters are: 128 bytes capacity, 32 bytes per block, 2-way set associative.
  - Elements in the `bodies` array are aligned to the cache lines.
  - `sizeof(float) == 4`
  - You can ignore what `is_collide` exactly does and assume each body structure is loaded only *once* within the inner loop iteration (i.e., `bodies[i]` and `bodies[j]` are loaded into registers).
  - The variables `i`, `j` and `count` are stored in registers.
  - Instruction cache is not considered.
  - Assume the cache is initially empty.

  + Calculate the hit rate for the above code.
    #t4-1

  + How can the hit rate be improved by modifying only the code (without changing the cache configuration)? Briefly explain your solution.
    #t4-2

]
