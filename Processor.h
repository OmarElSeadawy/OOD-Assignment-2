#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "Instruction.h"
#include "InstructionFactory.h"
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#define MEMORYSIZE 1024

class Processor{

    private:

    int DataMemory[MEMORYSIZE] = {0};
    std::mutex MutexMemory[MEMORYSIZE];
    int FileNum;
    std::vector<std::thread> workers;
    std::mutex ReadMutex;

    public:
    
    Processor(int Fn):FileNum(Fn){}
    ~Processor(){}

    static void Execute(std::string fname, int DataMemory[],std::mutex MutexMemory[],int idx)
    {
        InstructionFactory IF;
        int IMemorySize;
        int ProgramCounter;
        Instruction** InstructionMemory = new Instruction*[MEMORYSIZE];

        try
        {
               IMemorySize = IF.ParseFile(fname+std::to_string(idx+1)+".txt", DataMemory,MutexMemory,InstructionMemory);       //Sending Array by Reference
               ProgramCounter = 0;                         //Program Counter
               std::cout << "Program Counter : " << ProgramCounter << " ImemorySize : " << IMemorySize << " At Thread : " << idx << std::endl;
                
            while (ProgramCounter < IMemorySize) {
                std::cout << "Program Counter : " << ProgramCounter << " At Thread : " << idx << std::endl;
                (*InstructionMemory[ProgramCounter]).Execute(ProgramCounter);   // Execution of Functions
                if((ProgramCounter >= IMemorySize)||(ProgramCounter<0))          /* This is used incase Jump Function Bypassed the limit of instruction memory*/
                    throw -1;
                }    
        }
        catch(int e)         /*Exception Handling*/
        {  
            std::cerr << "Exception Caught in Thread : " << idx+1 << std::endl;
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
            
            for(int j=0;j<IMemorySize;j++)
                delete InstructionMemory[j];
            delete[] InstructionMemory;
            
        };

    }
    
    void Run(std::string fname)
    {
        std::cout << "Starting to Thread\n";
         for(int i=0;i<FileNum;i++)
             {
                 std::cout << "Creating Thread " << i << std::endl;
                 std::thread t(&Processor::Execute,fname,DataMemory,MutexMemory,i);
                 workers.push_back(std::move(t));
             }

         for(std::thread& t: workers)
             t.join();

        std::cout << "All Threads Joined Succesfully " << std::endl;
    }
};

#endif