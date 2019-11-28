#ifndef INSTRUCTIONMULT_H
#define INSTRUCTIONMULT_H

#include "Instruction.h"
#include "Parameters.h"
#include <iostream>

class InstructionMult : public Instruction
{
    public:
    ~InstructionMult(){
        std::cout << "MULT INSTRUCTION Destructor\n";
    };
    InstructionMult(parameters* params):Instruction(params){
        std::cout << "MULT Instruction Constructor\n";
    };

    void Execute(int &PC)
    {
        std::cout << "Executing Mult COMMAND\n";
		int operand1, operand2;
		if (p->isp1addr)
			operand1 = *p->p1.param1addr;
		else
			operand1 = p->p1.param1val;

		if (p->isp2addr)
			operand2 = *p->p2.param2addr;
		else
			operand2 = p->p2.param2val;


		*p->p3.param3addr = operand1 * operand2;
		PC++;
    }
    
};


#endif