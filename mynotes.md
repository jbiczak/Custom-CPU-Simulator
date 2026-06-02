# The CPU Design Notes

## Project's Direction

The first version of this project will focus on a software CPU simulator in C++.This allows the CPU architecture to be tested before adding physical hardware.
Later, the simulator can communicate with an STM32 board over serial communication to display register or memory values.

## Version 1 CPU Components

### Registers

The CPU has 4 registers (so far):

- R0
- R1
- R2
- R3

Each register stores an integer value.



### Memory

The CPU has 256 memory locations.

Each memory location stores an integer.



### ALU

The ALU currently supports:

- ADD
- SUB
-

More may/will be added

### Instructions

LOAD R, value  
Loads a number into a register.

ADD destination, source1, source2  
Adds two source registers and stores the result in the destination register.

SUB destination, source1, source2  
Subtracts the second source register from the first source register.

STORE register, address  
Stores a register value into memory.

HALT  
Stops execution.



## Hardware Visualization Idea

Once the software simulator is working, an STM32 board could be used to display the CPU state.

Possible hardware outputs:

- LED/s showing register values in binary
- LCD display showing register values
- Button input to step through instructions
- Serial communication between the laptop and STM32
- Adding a
-

## Current CPU Model (open to modifications)

        Instructions
             |
             v
        CPU Functions
             |
             v
     -------------------
     |                 |
     Registers       ALU
     |                 |
     -------------------
             |
             v
           Memory