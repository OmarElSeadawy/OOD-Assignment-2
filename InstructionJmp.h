#ifndef INSTRUCTIONJMP_H
#define INSTRUCTIONJMP_H

#include "Instruction.h"
#include "Parameters.h"
#include <iostream>

class InstructionJmp : public Instruction
{
    public:
    ~InstructionJmp(){
        std::cout << "Jmp Instruction Destructor\n";
    };
    InstructionJmp(parameters* params):p(params){
        std::cout << "Jmp Instruction Constructor\n";
    };
    parameters *p;

    void Execute(int &PC)
    {
        int in;
        std::cout << "Executing Jmp COMMAND\n";
        PC = (p->p1.param1val) - 1;
    }
    
};


#endif