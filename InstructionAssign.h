#ifndef INSTRUCTIONAssign_H
#define INSTRUCTIONAssign_H

#include "Instruction.h"
#include "Parameters.h"
#include <iostream>

class InstructionAssign : public Instruction
{
    public:
    ~InstructionAssign(){
        std::cout << "Assign Instruction Destructor\n";
    };
    InstructionAssign(parameters* params):p(params){
        std::cout << "Assign Instruction Constructor\n";
    };
    parameters *p;

    void Execute(int &PC)
    {
        std::cout << "Executing Assign COMMAND\n";
		int operand1;
		if (p->isp1addr)
			operand1 = *p->p1.param1addr;
		else
			operand1 = p->p1.param1val;

		*p->p2.param2addr = operand1;
		PC++;
    }
    
};


#endif