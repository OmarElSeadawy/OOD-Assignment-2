#ifndef INSTRUCTIONLE_H
#define INSTRUCTIONLE_H

#include "Instruction.h"
#include "Parameters.h"
#include <iostream>

class InstructionLE : public Instruction
{
    public:
    ~InstructionLE(){
        std::cout << "LE INSTRUCTION Destructor\n";
    };
    InstructionLE(parameters* params):p(params){
        std::cout << "LE Instruction Constructor\n";
    };
    parameters *p;

    void Execute(int &PC)
    {
        std::cout << "Executing LE COMMAND\n";
		int operand1, operand2;
		if (p->isp1addr)
			operand1 = *p->p1.param1addr;
		else
			operand1 = p->p1.param1val;

		if (p->isp2addr)
			operand2 = *p->p2.param2addr;
		else
			operand2 = p->p2.param2val;

        if(operand1 <= operand2)
            *p->p3.param3addr = 1;
        else
            *p->p3.param3addr = 0;
		PC++;
    }
    
};


#endif