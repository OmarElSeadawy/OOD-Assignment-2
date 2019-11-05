#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include "Parameters.h"
#include "Instruction.h"
#include "InstructionAdd.h"
#include "InstructionFactory.h"

#define MEMORYSIZE 1024
//std::vector<Instruction*> InstructionMemory;
Instruction** InstructionMemory = new Instruction*;
int DataMemory[MEMORYSIZE] = {0};

int main()
{
    InstructionFactory IF("program.txt");
    try{
        int IMemorySize = IF.ParseFile(DataMemory,InstructionMemory);       //Sending Array by Reference
        int ProgramCounter = 0;                                             // Program Counter
        while (ProgramCounter < IMemorySize) {
            (*InstructionMemory[ProgramCounter]).Execute(ProgramCounter);   // Execution of Functions
            if((ProgramCounter >= IMemorySize)||(ProgramCounter<0))          /* This is used incase Jump Function Bypassed the limit of instruction memory*/
                throw -1;
             }
    }
    catch(int e)         /*Exception Handling*/
    {  
        switch(e)
        {
            case -1: //JMP Command Instruction out of bound
            std::cerr << "Instruction Address out of bound\n";
            break;

            case -2: //Incorrect Parameter Value
            std::cerr << "Incorrect Parameter Value Exception Caught\n";
            break;

            case -3: //Incorrect Instruction
            std::cerr << "Incorrect Instruction Exception Caught\n";
            break;

            case -9: //System Halt Command
            std::cerr << "SYSTEM HALT COMMAND - Processor Shutdown\n";
            break;

            default:
            std::cerr << "Unhandled Exception Caught\n";
        }
    };
    
    return 0;
}
