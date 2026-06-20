# Custom CPU Simulator WITH Hardware Visualization

This summer 2026 project project is an educational CPU simulator built from scratch in C++ (VSCode)

My first goal is to simulate the "core" components of a simple CPU:

- Registers
- Memory
- ALU operations
- Basic instructions
- Instruction execution

The longer-term goal is to connect the simulator to an STM32 board (preferably one used in previous projects) so that register or memory values can be visualized using LEDs, buttons, or another hardware interface.

## The Initial CPU Design

- 4 general-purpose registers: R0, R1, R2, R3 (more may be added)
- 256 memory locations
- Integer-based data representation
- Basic instructions:
  - LOAD
  - ADD
  - SUB
  - STORE
  - HALT

## Current Progress (as of JUNE 2026)

The current simulator can:

- Load values into registers
- Add two register values
- Subtract two register values
- Store register values into memory
- Print register and memory states
- The goals marked as "Completed" below

## Current Goals ()

- Add a program counter (Completed)
- Implement a fetch-decode-execute cycle (Completed)
- Create an instruction format (Completed)
- Upgrade the simulator so programs can now be written in a simple assembly-style format (Completed)
- Add branching instructions (Completed)
- Add performance tracking (Completed)
- Create an external .asm file loader: read programs from disk, ignore blank lines/comments, programs/ folder structure (Completed)
- Expanded instructions support: ADDI, SUBI, MUL, MOV, CMP, etc; later AND/OR/XOR/SHL/SHR (Currently working on...)
- Connect the simulator to STM32 hardware for visualization