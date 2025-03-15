.globl simple_fn naive_mod mul_arr 

.data
failure_message: .asciiz "Test failed for some reason.\n"
success_message: .asciiz "Sanity checks passed! Make sure there are no calling convention violations.\n"
array:
    .word 1 2 3 4 5
exp_inc_array_result:
    .word 1 4 9 16 25

.text
main:
    # We test our program by loading a bunch of random values
    # into a few saved registers - if any of these are modified
    # after these functions return, then we know calling
    # convention was broken by one of these functions
    li s0, 2623
    li s1, 2910
    # ... skipping middle registers so the file isn't too long
    # If we wanted to be rigorous, we would add checks for
    # s2-s10 as well
    li s11, 134
    # Now, we call some functions
    # simple_fn: should return 2025
    jal simple_fn # Shorthand for "jal ra, simple_fn"
    li t0, 2025
    bne a0, t0, failure
    # naive_mod should return 1024 mod 217 = 156
    li a0, 1024
    li a1, 217
    jal naive_mod
    li t0, 156
    bne a0, t0, failure
    # mul_arr: similar to "dot multiply" in matlab
    la a0, array
    li a1, 5
    jal mul_arr
    jal check_arr # Verifies mul_arr and jumps to "failure" on failure
    li t0, 2623
    li t1, 2910
    li t2, 134
    bne s0, t0, failure
    bne s1, t1, failure
    bne s11, t2, failure
     # If none of those branches were hit, print a message and exit normally
    li a0, 4
    la a1, success_message
    ecall
    li a0, 10
    ecall

# Just a simple function. Returns 2025.
#
# DONE: Fix the reported error in this function (you can delete lines
# when necessary, as long as the function still returns 2025 in a0).
simple_fn:
    li a0, 2025
    ret

# Computes a0 mod a1.
# This is analogous to the following C pseudocode:
#
# uint32_t naive_mod(uint32_t a0, uint32_t a1) {
#     uint32_t s0 = a0;
#     while (s0 < a1) {
#         s0 -= a1;
#     }
#     return s0;
# }
#
# DONE: There's a calling convention error with this function!
# The big all-caps comments should give you a hint about what's
# missing. Another hint: what does the "s" in "s0" stand for?
naive_mod:
    # BEGIN PROLOGUE
    addi sp, sp, -4
    sw s0, 0(sp)
    # END PROLOGUE
    mv s0, a0
naive_mod_loop:
    blt s0, a1, naive_mod_end
    sub s0, s0, a1
    j naive_mod_loop
naive_mod_end:
    mv a0, s0
    # BEGIN EPILOGUE
    lw s0, 0(sp)
    addi sp, sp, 4
    # END EPILOGUE
    ret

# Multiplies the elements of an array in-place.
# a0 holds the address of the start of the array, and a1 holds
# the number of elements it contains.
#
# This function calls the "helper_fn" function, which takes in an
# address as argument and multiplies the 32-bit value stored there
# by itself.
mul_arr:
    # BEGIN PROLOGUE
    #
    # FIXME: What other registers need to be saved?
    #
    addi sp, sp, -4
    sw ra, 0(sp)
    # END PROLOGUE
    mv s0, a0 # Copy start of array to saved register
    mv s1, a1 # Copy length of array to saved register
    li t0, 0 # Initialize counter to 0
inc_arr_loop:
    beq t0, s1, inc_arr_end
    slli t1, t0, 2 # Convert array index to byte offset
    add a0, s0, t1 # Add offset to start of array
    # Prepare to call helper_fn
    #
    # FIXME: Add code to preserve the value in t0 before we call helper_fn
    # Hint: What does the "t" in "t0" stand for?
    # Also ask yourself this: why don't we need to preserve t1?
    #
    jal helper_fn
    # Finished call for helper_fn
    addi t0, t0, 1 # Increment counter
    j inc_arr_loop
inc_arr_end:
    # BEGIN EPILOGUE
    lw ra, 0(sp)
    addi sp, sp, 4
    # END EPILOGUE
    ret

# This helper function adds 1 to the value at the memory address in a0.
# It doesn't return anything.
# C pseudocode for what it does: "*a0 = *a0 * *a0"
#
# DONE: This function also violates calling convention, but it might not
# be reported by the Venus calling convention checker (try and figure out why).
# You should fix the bug anyway by filling in the prologue and epilogue
# as appropriate.
helper_fn:
    # BEGIN PROLOGUE
    addi sp, sp, -4
    sw s0, 0(sp)
    # END PROLOGUE
    lw t1, 0(a0)
    mul s0, t1, t1
    sw s0, 0(a0)
    # BEGIN EPILOGUE
    lw s0, 0(sp)
    addi sp, sp, 4
    # END EPILOGUE
    ret


# YOU CAN IGNORE EVERYTHING BELOW THIS COMMENT

check_arr:
    la t0, exp_inc_array_result
    la t1, array
    addi t2, t1, 20 # Last element is 5*4 bytes off
check_arr_loop:
    beq t1, t2, check_arr_end
    lw t3, 0(t0)
    lw t4, 0(t1)
    bne t3, t4, failure
    addi t0, t0, 4
    addi t1, t1, 4
    j check_arr_loop
check_arr_end:
    ret
    

# This isn't really a function - it just prints a message, then
# terminates the program on failure. Think of it like an exception.
failure:
    li a0, 4 # String print ecall
    la a1, failure_message
    ecall
    li a0, 10 # Exit ecall
    ecall
    
# end