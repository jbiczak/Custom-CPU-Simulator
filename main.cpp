#include <iostream>
#include <array>
#include <vector> // to store lists of instructions as a program in the future
#include <string> // for parsing instructions: LOAD, ADD, SUB, STORE, etc.
using namespace std;

/*
    Instruction struct represents one instruction in our simulated CPU program.
    For now, each instruction has:
    - operation: the instruction name, like LOAD, ADD, SUB, STORE, HALT
    - arg1: first argument
    - arg2: second argument
    - arg3: third argument

    ex: Instruction("ADD", 3, 1, 2) = ADD R3, R1, R2
*/
struct Instruction {
    string operation;
    int arg1;
    int arg2;
    int arg3;

    Instruction(string op, int a1, int a2, int a3) {
        operation = op;
        arg1 = a1;
        arg2 = a2;
        arg3 = a3;
    }
};

class CPU {
private:
    array<int, 4> registers; // creates the 4 registers (R0, R1, R2, R3)
    array<int, 256> memory; //creates 256 memory spots
    /*
        The program counter (PC) keeps track of which instruction
        the CPU is currently executing.
    */
    int programCounter;

public:

    /* Constructor:
    This runs automatically when we create a CPU object in main().
    It initializes all registers and memory locations to 0,
    which gives the CPU a clean starting state.  */
    CPU() {
        registers.fill(0);
        memory.fill(0);
        programCounter = 0; // CPU starts executing from the first instruction
    }



    /* LOAD instruction:
    Places an immediate value directly into a register.
    
    example:
    load(1, 10) means LOAD R1, 10   */
    void load(int reg, int value) {
        // Before accessing the register array, make sure the register number is valid.
        // This prevents trying to access something like R9, which does not exist.
        if (isValidRegister(reg)) {
            registers[reg] = value;
        } else {
            cout << "Invalid register R" << reg << endl;
        }
    }
    /* ADD instruction:
    Adds the values from two source registers and stores the result
    in a destination register.
    
    example:
    add(3, 1, 2) means ADD R3, R1, R2    */
    void add(int dest, int src1, int src2) {
        // Check that all three register numbers are valid before doing the operation.
        if (isValidRegister(dest) && isValidRegister(src1) && isValidRegister(src2)) {
            registers[dest] = registers[src1] + registers[src2]; // The ALU takes two inputs and produces one output.
        } else {
            cout << "Invalid register used in ADD instruction" << endl;
        }
    }
    /* SUB instruction:
    Subtracts the value in src2 from the value in src1,
    then stores the result in the destination register.
    
    // Example:
    // sub(3, 1, 2) means SUB R3, R1, R2   */

    void sub(int dest, int src1, int src2) {
        if (isValidRegister(dest) && isValidRegister(src1) && isValidRegister(src2)) {
            registers[dest] = registers[src1] - registers[src2];
        } else {
            cout << "Invalid register used in SUB instruction" << endl;
        }
    }
    // STORE instruction:
    // Copies the value from a register into a memory location.
    void store(int reg, int address) {
        if (isValidRegister(reg) && isValidMemoryAddress(address)) {
            memory[address] = registers[reg];
        } else {
            cout << "Invalid STORE instruction" << endl;
        }
    }

//===================================( RUN PROGRAM )===================================================
    void runProgram(vector<Instruction> program) {
    bool running = true;
    programCounter = 0; // start at the first instruction.
    while (running && programCounter < program.size()) {
        /*
            FETCH:Get the instruction at the current program counter.
        */
        Instruction currentInstruction = program[programCounter];
        cout << "PC = " << programCounter
             << " | Executing: " << currentInstruction.operation << endl;
        /*
            DECODE + EXECUTE---> Look at the operation name and call the correct CPU function
        */
        if (currentInstruction.operation == "LOAD") {
            //Instruction("LOAD", register, value, unused)
            load(currentInstruction.arg1, currentInstruction.arg2);

        } else if (currentInstruction.operation == "ADD") {
            //Instruction("ADD", destination, source1, source2)
            add(currentInstruction.arg1, currentInstruction.arg2, currentInstruction.arg3);

        } else if (currentInstruction.operation == "SUB") {
            //Instruction("SUB", destination, source1, source2)
            sub(currentInstruction.arg1, currentInstruction.arg2, currentInstruction.arg3);

        } else if (currentInstruction.operation == "STORE") {
            // Instruction("STORE", register, memoryAddress, unused)
            store(currentInstruction.arg1, currentInstruction.arg2);

        } else if (currentInstruction.operation == "HALT") {
            // HALT: tells the CPU to stop running the program.
            running = false;
            cout << "HALT reached. Program stopped." << endl;

        } else {
            cout << "Unknown instruction: " << currentInstruction.operation << endl;
            running = false;
        }
        //Move to the next instruction. Later, branch/jump instructions can change the PC differently
        programCounter++;
        cout << endl;
    }
}

//=======================================================================================================

    void printRegisters() {
        cout << "Register State:" << endl;
        for (int i = 0; i < 4; i++) {
            cout << "R" << i << " = " << registers[i] << endl;
        }
    }

    void printMemory(int address) {
        if (isValidMemoryAddress(address)) {
            cout << "Memory[" << address << "] = " << memory[address] << endl;
        } else {
            cout << "Invalid memory address" << endl;
        }
    }

private:
    bool isValidRegister(int reg) {
        return reg >= 0 && reg < 4;
    }

    bool isValidMemoryAddress(int address) {
        return address >= 0 && address < 256;
    }
};

int main() {
    CPU cpu;

    cout << "Running Custom CPU Simulator..." << endl;
    cout << endl;

    /*  Simulated program:
    LOAD R1, 10
    LOAD R2, 5
    ADD R3, R1, R2
    STORE R3, 100    */

    cpu.load(1, 10); // LOAD R1, 10 --> R1 = 10
    cpu.load(2, 5);
    cpu.add(3, 1, 2); // ADD R3, R1, R2 --->
    /*  R3 = R1 + R2
        R3 = 10 + 5
        R3 = 15     */
    cpu.store(3, 100); // STORE R3, 100 --> Memory[100] = R3 = 15

    cout << "After ADD program:" << endl;
    cpu.printRegisters();
    cpu.printMemory(100);

    cout << endl;

    /*  Second test:
    SUB R3, R1, R2
    STORE R3, 101    */

    cpu.sub(3, 1, 2);
    cpu.store(3, 101);

    cout << "After SUB program:" << endl;
    cpu.printRegisters();
    cpu.printMemory(101);

    return 0;
}