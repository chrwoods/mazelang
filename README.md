# mazelang
Esoteric maze-based programming language

## Specification
Programs in Mazelang are written in the form of a maze, where the solution through the maze becomes the compiled code. There are two types of characters in Mazelang: empty and non-empty. Empty spaces make up open space in the maze, and non-empty spaces... don't. So a maze that looks like:

```
########
    #
### # ##
###   ##
########
```

is functionally identical to one that looks like:

```
ABCDEFGH
    I
JKL M NO
PQR   ST
UVWXYZ12
```

The starting point is chosen as the opening that is in the higher row, and if they are in the same row it is the one that is farther left.

## Instructions/Operators
This language is stack-based, with instructions based on the number of spaces in between each turn.

These are the following categories of commands, which are executed by the amount of spaces modulo 5 - i.e. 7 spaces would do an arithmetic command, since 7 % 5 is 2:

- 0: Do nothing

- 1: Control Flow

- 2: Arithmetic

- 3: Stack Manipulation

- 4: I/O

Each category then takes a certain number of parameters.

- Control Flow: This one deals with loops.

  - 0: Do nothing

  - 1: Pop the top number off the stack and, if the new top of the stack is not 0, repeats the popped number of instructions again. For instance, if the popped number is 5 it will repeat the last 5 commands.

  - 2: Pops the top two numbers off the stack - the first number will be how many times to loop, the second number will be how many of the next commands to loop. 

- Arithmetic: This one is pretty simple, it will take the top two numbers of the stack and merge them into a single number on the top of the stack with the appropriate operation, where the second number in the stack is modified by the first number (i.e. if the stack is 8, 10, 5, then subtract would pop 8 and 10, then take 10 - 8 = 2 and push the 2 back onto the stack, making the new stack 2, 5).

  - 0: Not (with number on top of stack, non-zero becomes zero, zero becomes one)

  - 1: Add
  
  - 2: Subtract
  
  - 3: Multiply
  
  - 4: Divide (integer division)
  
  - 5: Modulo
  
  - 6: Exponential
  
  - 7: Bitwise OR
  
  - 8: Bitwise AND

- Stack Manipulation: This one is also pretty straightforward, it will either push a new number to the stack or shift it around.

  - 0: Manipulate
  
    - 1: Discard top of stack

    - 2: Roll stack (pops the first number on the stack and places the new top of the stack that many deeper into the stack, i.e. a stack of 3, 5, 7, 9, 11, 13, 15 will become 7, 9, 5, 11, 13, 15)
    
    - 3: Swap top two numbers of stack

    - 4: Duplicate top of stack

  - 1-9: Add new number to stack with given number of digits, which is then followed by that many parameters (i. e. 5 6 7 8 9 0 would push the 5 digit number 67890 onto the top of the stack)

- I/O: Reads in or prints out from the top of the stack

  - 0: Read in a single character onto the top of the stack

  - 1: Pops the top of the stack and prints it out, mod 256, as an ASCII character

  - 2: Reads in a number onto the top of the stack

  - 3: Pops the top of the stack and prints it as a number