.section .text
.globl draw
.type draw, @function
draw:
	li a0,50
	li a1,20
	li a2,150
	li a3,60
	li a4,62345
	addi sp,sp,-4
	sw ra,0(sp)
	jal LCD_DrawRectangle
	lw ra,0(sp)
	addi sp,sp,4
