.section .text
.globl draw
.type draw, @function
draw:
	li a0,10
	li a1,27
	li a2,150
	li a3,40
	li a4,62345
	addi sp,sp,-4
	sw ra,0(sp)
	jal LCD_DrawRectangle
	lw ra,0(sp)
	addi sp,sp,4
