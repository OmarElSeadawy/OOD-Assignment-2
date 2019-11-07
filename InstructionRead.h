#ifndef INSTRUCTIONREAD_H
#define INSTRUCTIONREAD_H

#include "Instruction.h"
#include "Parameters.h"
#include <iostream>

class InstructionRead : public Instruction
{
    public:
    ~InstructionRead(){
        std::cout << "Read Instruction Destructor\n";
    };
    InstructionRead(parameters* params):Instruction(params){
        std::cout << "Read Instruction Constructor\n";
    };

    void Execute(int &PC)
    {
        int in;
        std::cout << "Executing Read COMMAND\n";
        std::cout << "Please enter value you would like to put in Memory : ";
        std::cin >> in;
        *p->p1.param1addr = in;
		PC++;
    }
    
};


#endif