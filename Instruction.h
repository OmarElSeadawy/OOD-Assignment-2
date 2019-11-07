#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include "Parameters.h"

class Instruction
{
    protected:
    parameters *p;
    
    public:
    Instruction(){}
    virtual void Execute(int &PC) = 0;   
    Instruction(parameters* params):p(params){}
    virtual ~Instruction()
    {
        delete p->p1.param1addr;
        delete p->p2.param2addr;
        delete p->p3.param3addr;
        delete p;
    }
};


#endif