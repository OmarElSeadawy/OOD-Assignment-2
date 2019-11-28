#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "Instruction.h"
#include "InstructionFactory.h"
#include <string>
#define MEMORYSIZE 1024


class Processor{

    private:

    Instruction** InstructionMemory;
    int DataMemory[MEMORYSIZE] = {0};
    std::string programfilename;
    InstructionFactory IF;
    int ProgramCounter;
    int IMemorySize;
    
    public:
    
    Processor():InstructionMemory(new Instruction*),ProgramCounter(0){ }
    ~Processor()
    {
        for(int i = 0; i < IMemorySize; i++)
            delete[] InstructionMemory[i];
        delete [] InstructionMemory;
    }

    void Execute(std::string fname)
    {
        programfilename = fname;
        try
        {
            IMemorySize = IF.ParseFile(programfilename, DataMemory,InstructionMemory);       //Sending Array by Reference
            ProgramCounter = 0;                                             // Program Counter
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
                
                case -4:
                std::cerr << "Data Memory out of Bound\n";
                break;

                case -7:
                std::cerr << "Invalid Read Value\n";
                break;

                case -9: //System Halt Command
                std::cerr << "SYSTEM HALT COMMAND - Processor Shutdown\n";
                break;

                default:
                std::cerr << "Unhandled Exception Caught\n";
            }
        };
        

    }
};



#endif