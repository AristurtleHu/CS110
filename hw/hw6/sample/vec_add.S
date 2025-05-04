li t0, 16
li t1, 0
li a0, 0x100
li a1, 0x200
slli t2, t1, 2
add t3, a0, t2
lw t4, 0(t3)
add t5, a1, t2
lw t6, 0(t5)
add t4, t4, t6
addi x0, x0, 0
addi x0, x0, 0
sw t4, 0(t3)
addi t1, t1, 1
bne t0, t1, -40
