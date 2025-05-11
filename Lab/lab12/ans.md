### Differences in "load" Intrinsics:

1.  **`_mm_load_si128 (__m128i const* mem_addr)`**:
    *   **Purpose**: Loads 128 bits of integer data from memory into a `__m128i` register.
    *   **Alignment**: The memory address `mem_addr` **must be 16-byte aligned**. Failure to meet this alignment requirement will typically result in a general-protection exception (segmentation fault).
    *   **Data Type**: Integer data (e.g., `char`, `short`, `int`, `long long`).

2.  **`_mm_loadu_si128 (__m128i const* mem_addr)`**:
    *   **Purpose**: Loads 128 bits of integer data from memory into a `__m128i` register.
    *   **Alignment**: The memory address `mem_addr` **does not need to be 16-byte aligned** (the 'u' stands for "unaligned").
    *   **Performance**: Generally slower than `_mm_load_si128` if the data happens to be unaligned, as it might involve more complex hardware operations. If the data is aligned, performance can be similar.
    *   **Data Type**: Integer data.

3.  **`_mm_load_pd (double const* mem_addr)`**:
    *   **Purpose**: Loads two packed double-precision floating-point values (2 x 64-bit = 128 bits) from memory into an `__m128d` register.
    *   **Alignment**: The memory address `mem_addr` **must be 16-byte aligned**.
    *   **Data Type**: Double-precision floating-point values (`double`).

4.  **`_mm_load1_pd (double const* mem_addr)`** (also known as `_mm_load_sd` and broadcast):
    *   **Purpose**: Loads a single double-precision floating-point value from memory and broadcasts it to both 64-bit elements of the `__m128d` register.
        *   `r0 = *mem_addr`
        *   `r1 = *mem_addr`
    *   **Alignment**: The memory address `mem_addr` for the single `double` **must be 8-byte aligned**.
    *   **Data Type**: A single `double` value.

### Header Files for Intrinsics:

Generally, including `<immintrin.h>` is a good practice as it transitively includes most other necessary intrinsic headers like `<xmmintrin.h>` (SSE), `<emmintrin.h>` (SSE2), `<pmmintrin.h>` (SSE3), `<tmmintrin.h>` (SSSE3), `<smmintrin.h>` (SSE4.1), `<nmmintrin.h>` (SSE4.2), and AVX/AVX2/AVX512 headers.

However, to be specific:

1.  **`__m128i _mm_abs_epi16 (__m128i a)`**:
    *   Requires: `<tmmintrin.h>` (SSSE3)
    *   Including `<immintrin.h>` is sufficient.

2.  **`__m128i _mm_add_epi32 (__m128i a, __m128i b)`**:
    *   Requires: `<emmintrin.h>` (SSE2)
    *   Including `<immintrin.h>` is sufficient.

3.  **`__m128 _mm_ceil_ps (__m128 a)`**:
    *   Requires: `<smmintrin.h>` (SSE4.1)
    *   Including `<immintrin.h>` is sufficient.

4.  **`_mm_load1_pd (double const* mem_addr)`**:
    *   Requires: `<emmintrin.h>` (SSE2)
    *   Including `<immintrin.h>` is sufficient.

**In summary, for all the listed intrinsics, including `<immintrin.h>` will provide the necessary declarations.**

### Why -O3 Makes Programs Faster

The `-O3` compiler flag enables a high level of optimization, instructing the compiler to apply a wide range of aggressive techniques to improve runtime performance. These techniques generally make programs faster by:

*   **Reducing Instruction Count**: Through methods like function inlining (eliminating function call overhead), dead code elimination, and more effective constant folding and propagation.
*   **Improving Instruction-Level Parallelism (ILP)**: By reordering instructions (instruction scheduling) to make better use of the CPU's multiple execution units and minimize pipeline stalls.
*   **Enhancing Data Locality**: Optimizing loops (e.g., loop unrolling, loop fusion, loop interchange) to improve cache utilization, thereby reducing the time spent waiting for data from memory.
*   **Utilizing SIMD Instructions (Auto-vectorization)**: Where appropriate, the compiler automatically converts scalar operations (operating on single data items) into vector operations (SIMD - Single Instruction, Multiple Data) that can process multiple data elements simultaneously.
*   **Optimizing Memory Access**: Through more sophisticated register allocation, keeping frequently used variables in fast CPU registers instead of slower main memory. It can also involve reordering memory operations for better efficiency.
*   **More Aggressive Heuristics**: `-O3` enables optimizations that might be considered too aggressive or too compile-time intensive for lower optimization levels. These can include more complex data flow analyses and transformations.

Essentially, `-O3` allows the compiler to spend significantly more time and effort analyzing the code to find and apply transformations that result in fewer machine instructions, instructions that execute faster, or instructions that are scheduled more efficiently for the target processor. This often leads to substantial speedups, especially for computationally intensive code. However, it can also increase compilation time and sometimes result in larger binary sizes.
