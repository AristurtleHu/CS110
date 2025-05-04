.section .text
.globl draw
.type draw, @function
draw:
	li a0,120
	li a1,15
	li a2,8
	li a3,65535
	addi sp,sp,-4
	sw ra,0(sp)
	jal LCD_DrawRectangle
	lw ra,0(sp)
	addi sp,sp,4
