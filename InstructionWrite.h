#ifndef INSTRUCTIONWRITE_H
#define INSTRUCTIONWRITE_H

#include "Instruction.h"
#include "Parameters.h"
#include <iostream>

class InstructionWrite : public Instruction
{
    public:
    ~InstructionWrite(){
        // std::cout << "Write Instruction Destructor\n";
    };
    InstructionWrite(parameters* params):Instruction(params){
        // std::cout << "Write Instruction Constructor\n";
    };

    void Execute(int &PC)
    {
        std::scoped_lock(*(p->p1m));
        std::cout << "Executing Write COMMAND\n";
		if (p->isp1addr)
			std::cout <<  *p->p1.param1addr << std::endl;
		else
			std::cout <<  p->p1.param1val << std::endl;
		PC++;
        p->p1m->unlock();
    }
    
};


#endif