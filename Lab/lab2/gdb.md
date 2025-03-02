# GDB Commands and Usage

`b main.c:7`
#### How do you pass command line arguments to a program when using gdb?
`run arg1 arg2 arg3`
- or `set args arg1 arg2 arg3` and then `run`

#### How do you set a breakpoint which only occurs when a set of conditions is true (e.g. when certain variables are a certain value)?
`break main.c:8 if queue->size > 2 && ...`
- next line of `for`

#### How do you execute the next line of C code in the program after stopping at a breakpoint?
`n`

#### How do you tell GDB that you want to debug the code inside the function instead?
`s`

#### How do you resume the program after stopping at a breakpoint?
`c`

#### How can you see the value of a variable (or even an expression like 1+2) in gdb?
`p expr`

#### How do you configure gdb so it prints the value of a variable after every step ?
`display expr`

#### How do you print a list of all variables and their values in the current function?
`info locals`

#### How do you exit out of gdb?
`q`