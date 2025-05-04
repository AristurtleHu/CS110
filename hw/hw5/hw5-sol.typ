#let sol = content => {
  box([*Solution: * #content], stroke: 1pt, inset: 10pt, width: 100%)
}

// Solution Example:
// #let t1 = (
//   [Yousr Ans],
//   [Yousr Ans],
//   [Yousr Ans],
//   [Yousr Ans],
// )
//
// #let t2-3 = sol[
//   Your Ans
// ]
//
// $ 1 + 1 = 2 $ for math equation

#let t1 = (
  [F],
  [F],
  [F],
  [F],
)

#let t2-1 = (
  [32],
  [256],
  [2],
  [8],
  [4],
  [5|2|5],
)

#let t2-2 = (
  [Miss],
  [Miss],
  [Miss],
  [Replacement],
  [Replacement],
  [Miss],
  [Replacement],
  [Hit],
  [Replacement],
  [Replacement],
  [Hit],
  [Hit],
  [Replacement],
  [Hit],
)

#let t2-3 = sol[
  Hit rate $= 4 / 14 = 2 / 7$.
  By changing it into a fully associative cache.
]


#let t3-1 = sol[
  Global Miss Rate $= 0.08 * 0.35 * 0.1 = 0.0028$.
]

#let t3-2 = sol[
  Memory Hit time $= 80 / 0.25 = 320$ cycles.

  AMAT $= 2 + 0.08 * (12 + 0.35 * (44 + 0.1 * 320)) = 5.088$ cycles.
]

#let t3-3 = sol[
  L1 hit time $= 2 * 1.6 = 3.2$ cycles.
  L1 local miss rate $= 0.06$.

  AMAT $= 3.2 + 0.06 * (12 + 0.35 * (44 + 0.1 * 320)) = 5.516$ cycles.
]


#let t4-1 = sol[
  Each block can store bodies[i] and bodies[i + 1].
  4 blocks, 2 sets in cache.

  Beacause of the cache associativity, we can have 2 bodies in the cache at a time. And bodies[i] is accessed each loop, so it will always be in the cache.

  For each i, accesses $= (64 - i) * 2$, hit $= floor((64 - i) / 2) + 64 - i - 1$.
  For $i >= 57$, all kept in cache, so hit = accesses.
  For $i = 63$, no access.

  In all, hit rate $= (sum_(i=1)^56 (floor((64 - i) / 2) + 64 - i - 1) + sum_(i=57)^63 ((64 - i) * 2)) / (sum_(i=1)^63 ((64 - i) * 2)) approx
  0.736$
]

#let t4-2 = sol[
  We can improve the hit rate by using cache blocking.

  #box[
    ```c
    #define N 64
    // Choose a block size B.
    #define B 4

    int check_collision_blocked() {
        int count = 0;

        for (int ii = 0; ii < N; ii += B) {
            for (int jj = ii; jj < N; jj += B) {
                int i_limit = min(ii + B, N);
                int j_limit = min(jj + B, N);

                for (int i = ii; i < i_limit; i++) {
                    int j_start = (ii == jj) ? i + 1 : jj; // ensure j > i

                    if (j_start < j_limit) {
                        for (int j = j_start; j < j_limit; j++) {
                            if (is_collide(bodies[i], bodies[j])) {
                                count++;
                            }
                        }
                    }
                }
            }
        }
        return count;
    }
    ```
  ]

  Cache blocking divides the `N x N` iteration space into smaller `B x B` blocks. The outer loops (`ii`, `jj`) iterate over these blocks. The inner loops (`i`, `j`) iterate within a block. By processing pairs `(bodies[i], bodies[j])` within a block `(ii, jj)`, we increase the likelihood that both `bodies[i]` and `bodies[j]` remain in the cache for subsequent accesses within that block.
]
