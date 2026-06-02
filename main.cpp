#include <iostream>
#include <array>
#include <vector> // to store lists of instructions as a program in the future
#include <string> // for parsing instructions: LOAD, ADD, SUB, STORE, etc.
using namespace std;

class CPU {
private:
    array<int, 4> registers; // creates the 4 registers (R0, R1, R2, R3)
    array<int, 256> memory; //creates 256 memory spots

public:

    /* Constructor:
    This runs automatically when we create a CPU object in main().
    It initializes all registers and memory locations to 0,
    which gives the CPU a clean starting state.  */
    CPU() {
        registers.fill(0);
        memory.fill(0);
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