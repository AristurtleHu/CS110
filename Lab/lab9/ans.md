# EX1

## Scenario 1

> What combination of parameters is producing the hit rate you observe? (Hint: Your answer should be the process of your calculation.)

Hit rate is 0. 
$$ 
\text{index} = (i * \text{step-size} * 4 / \text{block-size}) \mod \text{set-num}   
$$
All index is 0, no hit.

> What is our hit rate if we increase Rep Count arbitrarily? Why?

Still 0. No chance to hit.

> How could we modify our program parameters to maximize our hit rate?

Change step size to 1, option = 1. The hit rate is highest: 0.75.

## Scenario 2

> What combination of parameters is producing the hit rate you observe? (Hint: Your answer should be the process of your calculation.)

Hit rate is 0.75. Index = 0, 0, 1, 1, 2, 2, ... Each stores a[i] to a[i+4] and option = 1, so 4 access will hit 3. 

> What happens to our hit rate as Rep Count goes to infinity? Why?

Hit rate will be 1. Cache will put all elements needed of the array. So when rep becomes bigger, the hit rate will converge to 1.

> Suppose we have a program that uses a very large array and during each Rep, we apply a different operator to the elements of our array (e.g. if Rep Count = 1024, we apply 1024 different operations to each of the array elements). How can we restructure our program to achieve a hit rate like that achieved in this scenario? (Assume that the number of operations we apply to each element is very large and that the result for each element can be computed independently of the other elements.) What is this technique called?

The techinque is called Cache blocking.

```C
for (body1 = 0; body1 < NBODIES; body1 ++) {
   for (body2 = 0; body2 < NBODIES; body2++) {
     OUT[body1] += compute(body1, body2);
   }
}
```

If NBODIES is large enough, we will not reuse the data in cache at all, after modified

```C
for (body2 = 0; body2 < NBODIES; body2 += BLOCK) {
   for (body1 = 0; body1 < NBODIES; body1 ++) {
      for (body22 = 0; body22 < BLOCK; body22 ++) {
         OUT[body1] += compute(body1, body2 + body22);
      }
   }
}
```

We can set the BLOCK to be a proper value with the cache size, so that the data in cache will be reused finely.


## Scenario 3

> Run the simulation a few times. Every time, set a different seed value (bottom of the cache window). Note that the hit rate is non-deterministic. What is the range of its hit rate? Why is this the case? ("The cache eviction is random" is not a sufficient answer)

e.g., 0.0625, 0.125, 0.25, 0.3125, 0.375
rate $\in$ [0, 0.5]
0 stands for all choose the same block
0.5 stands for LRU

> Which Cache parameter can you modify in order to get a constant hit rate? Record the parameter and its value (and be prepared to show your TA a few runs of the simulation). How does this parameter allow us to get a constant hit rate? And explain why the constant hit rate value is that value.

Set associativity to 1, which turn the cache into a direct-mapped cache, we can get a constant hit rate. Hit rate is 0.5.

# EX2

> Why there is a gap between gb_v and gb_h ?

The performance of gb_h is better than gb_v. The data is more continuous in the horizontal direction. Using cache.

> Why the changed execution order will achieve a better performance even if we do more things(transpose)?

As the transpose operation is a fast enough, and as gb_h is much better than gb_v, so the performance will be better even two more transpose operations are added.

# EX3

As for the long array char, we define them at the last, so that they will not affect the cache line of the previous 2 int and the long type.


