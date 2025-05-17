### Q1

Depends on how the OS schedules threads.

### Q2

#### P2

Omp slices: 0.60405 seconds
        Max relative error: 0.000000e+00. Sanity check PASS
Omp chunks: 0.59384 seconds
        Max relative error: 0.000000e+00. Sanity check PASS


Mostly chunks run faster than slices. This is because chunks method run with rows consistently in the same thread, while slices method run with rows in different threads. This results in a higher cache usage.

By the way, slices might run faster than chunks in some cases, because chunks run into a problem of not balancing the workload. (cannot be divided evenly)

However, the difference is not significant, and both methods are efficient.

#### P3

Different usage of cache may differ the performance of the program. 

### Q3

*   **`Omp optimized` vs. `Omp reduction`:**
        *   Comparing the two, `Omp reduction` (e.g., 0.00221s for 15 threads) generally shows slightly better performance and scalability than `Omp optimized` (e.g., 0.00241s for 14 threads, 0.00242s for 15 threads).
        *   **Reason:** The `reduction` clause in OpenMP is a specialized directive. It allows the compiler and OpenMP runtime to implement the aggregation of results from different threads in a highly efficient manner. This often involves thread-private storage for partial results and optimized algorithms for their final combination, minimizing synchronization overhead and improving cache locality. A manual `Omp optimized` strategy, while effective, might not achieve the same level of fine-tuning as the built-in `reduction` mechanism.

#### Diminishing Returns and Performance Degradation with Increasing Threads

The results for `Omp optimized` and `Omp reduction` clearly show an initial performance improvement as threads are added, followed by diminishing returns, and eventually, performance degradation.

*   **Initial Speedup (e.g., 1 to ~8-14 threads):**
        As the number of threads increases, the workload is distributed, leading to faster execution times. The most significant gains are often seen when moving from 1 to 2 threads and continue as long as threads can run concurrently on available CPU cores.

*   **Diminishing Returns:**
        As more threads are added (e.g., in the range of 10-14 threads in the provided data), the performance improvement from each additional thread lessens. This is due to:
        *   **Amdahl's Law:** Every program has a sequential part that cannot be parallelized. This inherent serial fraction limits the maximum achievable speedup.
        *   **Parallel Overhead:** The costs associated with creating, managing, and synchronizing threads become more significant relative to the computational work done by each thread.

*   **Performance Degradation (e.g., beyond ~14-15 threads):**
        *   For `Omp optimized`, performance peaks around 14 threads (0.00241s) and then worsens (15 threads: 0.00242s, 16 threads: 0.00382s).
        *   For `Omp reduction`, performance peaks around 15 threads (0.00221s) and then worsens (16 threads: 0.00275s).
        *   **Reasons for Degradation:**
                1.  **Exceeding Physical Core Count:** When the number of active threads surpasses the number of available physical CPU cores, the operating system must resort to context switching. This process of saving and restoring thread states is computationally expensive and can negate the benefits of additional threads. The optimal number of threads is often related to the system's core count (including considerations for hyper-threading).
                2.  **Increased Resource Contention:** A higher number of threads leads to increased competition for shared hardware resources such as CPU caches (potentially causing cache thrashing) and memory bandwidth.
                3.  **Synchronization Bottlenecks:** Even with efficient reduction strategies, the final step of combining results from many threads can become a bottleneck. The coordination overhead for a large number of threads can outweigh the benefits of further parallelization.

### Q4

No taskwait will result in the situation that one thread calls merge function before two subarray are ready. This will cause the program to crash.

CUT_OFF too small will cause the program to run slower, because the overhead of creating threads is larger than the time saved by parallelizing the merge function.