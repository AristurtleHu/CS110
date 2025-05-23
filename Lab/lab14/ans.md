### Q1

3 bits for the page number, 5 bits for the offset
4 pages, each contains 32 Bytes

### Q2

00 20 40 60 80 a0 c0 e0 00 20

### Q3

Change memory size to contain 8 frames.
Therefore, the sequence of Q2 will result in 10 TLB misses and 8 page faults. 
