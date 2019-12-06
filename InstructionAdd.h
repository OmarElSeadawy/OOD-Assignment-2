#ifndef INSTRUCTIONADD_H
#define INSTRUCTIONADD_H

#include "Instruction.h"
#include "Parameters.h"

class InstructionAdd : public Instruction
{
    public:
    virtual ~InstructionAdd(){
        // std::cout << "Add Instruction Destructor\n";
    };
    InstructionAdd(parameters* params):Instruction(params){
        // std::cout << "Add Instruction Constructor\n";
    };

    void Execute(int &PC)
    {
        static int gcount = 0;
        // std::cout << "Locking Add Instruction " << ++gcount << std::endl;
        // std::cout << "Locking Memory Locations ; M1 : " << p->mi1 << " M2 : " << p->mi2 << " M3 : " << p->mi3 << std::endl; 
        int t = LockMutexes(p);
        // std::cout << "Locked Memory Locations ; M1 : " << p->mi1 << " M2 : " << p->mi2 << " M3 : " << p->mi3 << std::endl; 

        // std::cout << "Executing ADD COMMAND\n";
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

        UnlockMutexes(p,t);
        // std::cout << "Unlocking Memory Locations ; M1 : " << p->mi1 << " M2 : " << p->mi2 << " M3 : " << p->mi3 << std::endl; 

        // std::cout << "Unlocked Add Instruction " << gcount << std::endl;
    }
    
};


#endif