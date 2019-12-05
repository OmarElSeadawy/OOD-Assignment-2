#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "Instruction.h"
#include "InstructionFactory.h"
#include <string>
#include <vector>
#include <thread>
#define MEMORYSIZE 1024

class Processor{

    private:

    Instruction*** InstructionMemory;
    int DataMemory[MEMORYSIZE] = {0};
    int FileNum;
    std::vector<std::thread> workers;

    public:
    
    Processor(int Fn):FileNum(Fn){ 
        for(int ii = 0; ii < FileNum; ii++)
            InstructionMemory = new Instruction**;
            
    }
    ~Processor()
    {
        // for(int i = 0; i < IMemorySize[i]; i++)
        //     delete[] InstructionMemory[i];
        delete [] InstructionMemory;
    }

    void Execute(std::string fname, int idx)
    {
        InstructionFactory IF;
        int IMemorySize;
        int ProgramCounter;


        try
        {
               IMemorySize = IF.ParseFile(fname+std::to_string(idx+1), DataMemory,InstructionMemory[idx]);       //Sending Array by Reference
               ProgramCounter = 0;                         //Program Counter
                
            while (ProgramCounter < IMemorySize) {
                (*InstructionMemory[ProgramCounter])[idx].Execute(ProgramCounter);   // Execution of Functions
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
    
    void Run(std::string fname)
    {
        for(int i=0;i<FileNum;i++)
            {
                std::thread t(&Processor::Execute,fname,i);
                workers.push_back(t);
            }

        for(std::thread& t: workers)
            t.join();
    }
};

#endif