.data
test_input: .word 6 3 5 12

.text
main:
	add t0, x0, x0
	addi t1, x0, 4
	la t2, test_input
main_loop:
	beq t0, t1, main_exit
	slli t3, t0, 2
	add t4, t2, t3
	lw a0, 0(t4)
	# a0 = 6 3 5 12

	addi sp, sp, -20
	sw t0, 0(sp)
	sw t1, 4(sp)
	sw t2, 8(sp)
	sw t3, 12(sp)
	sw t4, 16(sp)

	jal ra, seriesOp

	lw t0, 0(sp)
	lw t1, 4(sp)
	lw t2, 8(sp)
	lw t3, 12(sp)
	lw t4, 16(sp)
	addi sp, sp, 20

	addi a1, a0, 0
	addi a0, x0, 1
	ecall # Print Result
	addi a1, x0, ' '
	addi a0, x0, 11
	ecall
	
	addi t0, t0, 1
	jal x0, main_loop
main_exit:  
	addi a0, x0, 10
	ecall # Exit

seriesOp: 
	# goal: change a0
	addi t0, a0, -1
	addi t1, x0, 1 # record the loop time
	seriesOp_loop:
	beq t0, x0, seriesOp_exit
	add t2, t0, x0
	andi t3, t1, 1 
	beq t3, x0, even_loop_time

	neg t2, t2 #t2 *= -1

	even_loop_time:
	add a0, a0, t2

	addi t1, t1, 1
	addi t0, t0, -1
	j seriesOp_loop

	seriesOp_exit:
	jr ra
