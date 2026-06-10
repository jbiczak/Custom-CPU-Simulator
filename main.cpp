#include <iostream>
#include <array>
#include <vector> // to store lists of instructions as a program
#include <string> // for parsing instructions: LOAD, ADD, SUB, STORE, etc.
#include <sstream> // for parsing instructions from text input
using namespace std;

/*
    Instruction struct represents one instruction in simulated CPU program.
    Each instruction has:
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
//====================================( PARSE REGISTER )===================================================
int parseRegister(string regText) {
    return regText[1] - '0'; // This converts 'R1' to 1, 'R2' to 2, etc
}
//====================================( PARSE INSTRUCTION )===================================================
Instruction parseInstruction(string line) { // Converts one assembly-style text instruction into an Instruction object.
    stringstream ss(line);                  // ADD R3, R1, R2  --> Instruction("ADD", 3, 1, 2)
    string operation;
    ss >> operation;

    if (operation == "LOAD") {
        string regText;
        int value;
        ss >> regText >> value;
        int reg = parseRegister(regText);
        return Instruction("LOAD", reg, value, 0);
    }

    else if (operation == "ADD") {
        string destText, src1Text, src2Text;
        ss >> destText >> src1Text >> src2Text;
        int dest = parseRegister(destText);
        int src1 = parseRegister(src1Text);
        int src2 = parseRegister(src2Text);
        return Instruction("ADD", dest, src1, src2);
    }
    else if (operation == "SUB") {
        string destText, src1Text, src2Text;

        ss >> destText >> src1Text >> src2Text;
        int dest = parseRegister(destText);
        int src1 = parseRegister(src1Text);
        int src2 = parseRegister(src2Text);
        return Instruction("SUB", dest, src1, src2);
    }
    else if (operation == "STORE") {
        string regText;
        int address;
        ss >> regText >> address;
        int reg = parseRegister(regText);
        return Instruction("STORE", reg, address, 0);
    }
    else if (operation == "JMP") {
        int targetAddress;
        ss >> targetAddress;
        return Instruction("JMP", targetAddress, 0, 0);
    }
//=================================( NEW CONDITIONAL INSTRUCTIONS )===================================================
    else if (operation == "BEQ") {
        string reg1Text, reg2Text;
        int targetAddress;
        ss >> reg1Text >> reg2Text >> targetAddress;
        int reg1 = parseRegister(reg1Text);
        int reg2 = parseRegister(reg2Text);
        return Instruction("BEQ", reg1, reg2, targetAddress);
    }

    else if (operation == "BNE") {
        string reg1Text, reg2Text;
        int targetAddress;
        ss >> reg1Text >> reg2Text >> targetAddress;
        int reg1 = parseRegister(reg1Text);
        int reg2 = parseRegister(reg2Text);
        return Instruction("BNE", reg1, reg2, targetAddress);
    }
//====================================================================================================================

    else if (operation == "HALT") {
        return Instruction("HALT", 0, 0, 0);
    }
    else {
        cout << "Parser error: unknown instruction " << operation << endl;
        return Instruction("HALT", 0, 0, 0); // If we encounter an unknown instruction, we return a HALT to stop the program.
    }
}
//====================================( PARSE PROGRAM )===================================================
vector<Instruction> parseProgram(vector<string> assemblyProgram) {
    vector<Instruction> program;
    for (string line : assemblyProgram) {
        program.push_back(parseInstruction(line));
    }
    return program;
// this is to convert a list of text instructions (assemblyProgram) into a list of Instruction objects that the CPU can execute.
// Each line of text is parsed into an Instruction using the parseInstruction function, and then added to the program vector.
}

class CPU {
private:
    array<int, 4> registers; // creates the 4 registers (R0, R1, R2, R3)
    array<int, 256> memory; //creates 256 memory spots
    /*
        The program counter (PC) keeps track of which instruction
        the CPU is currently executing.
    */
    int programCounter;

    // Performance metrics
    int instructionsExecuted;
    int cycleCount;
    int aluOperations;
    int memoryOperations;
    int branchInstructions;
    int branchesTaken;

public:

    /* Constructor:
    This runs automatically when create a CPU object in main().
    It initializes all registers and memory locations to 0,
    which gives the CPU a clean starting state.  */
    CPU() {
        registers.fill(0);
        memory.fill(0);
        programCounter = 0; // CPU starts executing from the first instruction

        // Initialize performance metrics to 0
        instructionsExecuted = 0;
        cycleCount = 0;
        aluOperations = 0;
        memoryOperations = 0;
        branchInstructions = 0;
        branchesTaken = 0;
    }

//===================================( CPU INSTRUCTION IMPLEMENTATIONS )===================================================
// This can be thought of as the ALU and control unit of the CPU, where we define how 
// each instruction works and how it manipulates data in registers and memory.

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
        instructionsExecuted++;
        /*
            DECODE + EXECUTE---> Look at the operation name and call the correct CPU function
        */
        if (currentInstruction.operation == "LOAD") {
            //Instruction("LOAD", register, value, unused)
            load(currentInstruction.arg1, currentInstruction.arg2);
            memoryOperations++;

        } else if (currentInstruction.operation == "ADD") {
            //Instruction("ADD", destination, source1, source2)
            add(currentInstruction.arg1, currentInstruction.arg2, currentInstruction.arg3);
            aluOperations++;

        } else if (currentInstruction.operation == "SUB") {
            //Instruction("SUB", destination, source1, source2)
            sub(currentInstruction.arg1, currentInstruction.arg2, currentInstruction.arg3);
            aluOperations++;

        } else if (currentInstruction.operation == "STORE") {
            // Instruction("STORE", register, memoryAddress, unused)
            store(currentInstruction.arg1, currentInstruction.arg2);
            memoryOperations++;

        } else if (currentInstruction.operation == "JMP") {
            // Instruction("JMP", targetAddress, unused, unused)
            branchInstructions++;
            branchesTaken++;
            programCounter = currentInstruction.arg1; // Sets the program counter to the target address to jump to that instruction.
            continue; // Skip the normal PC increment since we already set it to the jump target (standard behavior for a jump instruction)

        } else if (currentInstruction.operation == "BEQ") {
            // Instruction("BEQ", register1, register2, targetAddress)
            branchInstructions++;
            if (registers[currentInstruction.arg1] == registers[currentInstruction.arg2]) {
                branchesTaken++;
                programCounter = currentInstruction.arg3;
                continue;
            }
        } else if (currentInstruction.operation == "BNE") {
            // Instruction("BNE", register1, register2, targetAddress)
            branchInstructions++;
            if (registers[currentInstruction.arg1] != registers[currentInstruction.arg2]) {
                branchesTaken++;
                programCounter = currentInstruction.arg3;
                continue;
            }
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

// These values may be changed in the future if we want to add more registers or memory

};
//====================================( MAIN FUNCTION )===================================================
int main() {
    CPU cpu;

    cout << "Running Custom CPU Simulator..." << endl;
    cout << endl;

    /*  the simulated program:
    LOAD R1, 10
    LOAD R2, 5
    ADD R3, R1, R2
    STORE R3, 100


    SUB R3, R1, R2
    STORE R3, 101

    HALT
    */
/*================================( PREVIOUS INSTRUCTION-OBJECT PROGRAM 1 )===================================================
    vector<Instruction> program = {
        Instruction("LOAD", 1, 10, 0),      // LOAD R1, 10
        Instruction("LOAD", 2, 5, 0),       // LOAD R2, 5
        Instruction("ADD", 3, 1, 2),        // ADD R3, R1, R2
        Instruction("STORE", 3, 100, 0),    // STORE R3, 100

        Instruction("SUB", 3, 1, 2),        // SUB R3, R1, R2
        Instruction("STORE", 3, 101, 0),    // STORE R3, 101

        Instruction("HALT", 0, 0, 0)        // Stop the program
    };
*/
/*===============================( PREVIOUS ASSEMBLY-STYLE PROGRAM 2 )===================================================
    vector<string> assemblyProgram = {
        "LOAD R1, 10",
        "LOAD R2, 5",
        "ADD R3, R1, R2",
        "STORE R3, 100",

        "SUB R3, R1, R2",
        "STORE R3, 101",

        "HALT"
    };
*/
//====================================( NEW ASSEMBLY-STYLE PROGRAM WITH BRANCHING )===================================================
    vector<string> assemblyProgram = {
    "LOAD R1 0",       // R1 = counter, starts at 0
    "LOAD R2 1",       // R2 = increment value
    "LOAD R3 5",       // R3 = target value

    "ADD R1 R1 R2",    // R1 = R1 + 1
    "BNE R1 R3 3",     // if R1 != R3, jump back to instruction 3

    "STORE R1 120",    // store final counter value into memory
    "HALT"
};

    vector<Instruction> program = parseProgram(assemblyProgram); // Convert the assembly-style text instructions into Instruction objects
    
    
    
    cpu.runProgram(program); //CPU will fetch, decode, and execute each instruction until it hits HALT

    cout << "Final CPU State after program execution:" << endl;
    cpu.printRegisters(); ///prints the final values of all registers after the program finishes running
    cpu.printMemory(120); //should show 5, which is the final value of the counter after the loop finishes


    return 0;

}