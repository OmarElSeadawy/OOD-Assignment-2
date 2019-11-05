#ifndef INSTRUCTIONNEG_H
#define INSTRUCTIONNEG_H

#include "Instruction.h"
#include "Parameters.h"
#include <iostream>

class InstructionNeg : public Instruction
{
    public:
    ~InstructionNeg(){
        std::cout << "Neg Instruction Destructor\n";
    };
    InstructionNeg(parameters* params):p(params){
        std::cout << "Neg Instruction Constructor\n";
    };
    parameters *p;

    void Execute(int &PC)
    {
        std::cout << "Executing Neg COMMAND\n";
		int operand1;
		if (p->isp1addr)
			operand1 = *p->p1.param1addr;
		else
			operand1 = p->p1.param1val;

		*p->p2.param2addr = operand1 * -1;
		PC++;
    }
    
};


#endif