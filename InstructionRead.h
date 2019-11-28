#ifndef INSTRUCTIONREAD_H
#define INSTRUCTIONREAD_H

#include "Instruction.h"
#include "Parameters.h"
#include <iostream>
#include <algorithm>


class InstructionRead : public Instruction
{
    public:
    
    bool is_digits(const std::string &str)
    {
        return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
    }

    ~InstructionRead(){
        std::cout << "Read Instruction Destructor\n";
    };
    InstructionRead(parameters* params):Instruction(params){
        std::cout << "Read Instruction Constructor\n";
    };

    void Execute(int &PC)
    {
        std::string in;
        std::cout << "Executing Read COMMAND\n";
        std::cout << "Please enter value you would like to put in Memory : ";
        std::cin >> in;
        
        if((in[0] == '-') && (is_digits(in.substr(1,-1))))
            {
                *p->p1.param1addr = std::stoi(in);
		        PC++;
            }
        else if(is_digits(in))
            {
                *p->p1.param1addr = std::stoi(in);
                PC++;
            }
        else 
            throw -7;
        
    }
    
};


#endif