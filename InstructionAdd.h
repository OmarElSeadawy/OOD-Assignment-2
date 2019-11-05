#ifndef INSTRUCTIONADD_H
#define INSTRUCTIONADD_H

#include "Instruction.h"
#include "Parameters.h"

class InstructionAdd : public Instruction
{
    public:
    ~InstructionAdd(){
        std::cout << "Add Instruction Destructor\n";
    };
    InstructionAdd(parameters* params):p(params){
        std::cout << "Add Instruction Constructor\n";
    };
    parameters *p;

    void Execute(int &PC)
    {
        std::cout << "Executing ADD COMMAND\n";
		int operand1, operand2;
		if (p->isp1addr)
			operand1 = *p->p1.param1addr;
		else
			operand1 = p->p1.param1val;

		if (p->isp2addr)
			operand2 = *p->p2.param2addr;
		else
			operand2 = p->p2.param2val;

		*p->p3.param3addr = operand1 + operand2;
		PC++;
    }
    
};


#endif