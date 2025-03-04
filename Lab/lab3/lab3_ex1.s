.data
n: .word 9

.text
main:   add     t0, x0, x0
        addi    t1, x0, 1
        la      t3, n
        lw      t3, 0(t3)
fib:    beq     t3, x0, finish
        add     t2, t1, t0
        mv      t0, t1
        mv      t1, t2
        addi    t3, t3, -1
        j       fib

# In the finish label, we are going to 
# print an integer by system call instruction ECALL.
finish: addi    a0, x0, 1       # System call number for print integer
        addi    a1, t0, 0       # integer to print
        ecall                   # print integer ecall
        addi    a0, x0, 10
        ecall                   # terminate ecall

