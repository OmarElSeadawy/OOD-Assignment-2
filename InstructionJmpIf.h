#ifndef INSTRUCTIONJMPIF_H
#define INSTRUCTIONJMPIF_H

#include "Instruction.h"
#include "Parameters.h"
#include <iostream>

class InstructionJmpif : public Instruction
{
    public:
    ~InstructionJmpif(){
        std::cout << "Jmpif Instruction Destructor\n";
    };
    InstructionJmpif(parameters* params):p(params){
        std::cout << "Jmpif Instruction Constructor\n";
    };
    parameters *p;

    void Execute(int &PC)
    {
        int operand1;
        std::cout << "Executing Jmpif COMMAND\n";
        if (p->isp1addr)
			operand1 = *p->p1.param1addr;
		else
			operand1 = p->p1.param1val;

        if(operand1 == 0)
           {
                PC = (p->p2.param2val) - 1;
                std::cout << "JmpIf Success\n";
           } 
           else
            {
                PC++;
                std::cout << "JmpIf Failed\n";
            }
        
    }
    
};


#endif