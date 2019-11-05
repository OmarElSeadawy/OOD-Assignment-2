#ifndef INSTRUCTION_H
#define INSTRUCTION_H

class Instruction
{
    public:
    Instruction(){}
    virtual void Execute(int &PC) = 0;   
};


#endif