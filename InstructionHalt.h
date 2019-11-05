#ifndef INSTRUCTIONHALT_H
#define INSTRUCTIONHALT_H

#include "Instruction.h"
#include "Parameters.h"
#include <iostream>

class InstructionHalt : public Instruction
{
    public:
    ~InstructionHalt(){
        std::cout << "Halt Instruction Destructor\n";
    };
    InstructionHalt(parameters* params):p(params){
        std::cout << "Halt Instruction Constructor\n";
    };
    parameters *p;

    void Execute(int &PC)
    {
        throw -9;
    }
    
};


#endif