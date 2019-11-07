#ifndef INSTRUCTIONFACTORY_H
#define INSTRUCTIONFACTORY_H

#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Instruction.h"
#include "InstructionMult.h"
#include "InstructionAdd.h"
#include "InstructionLE.h"
#include "InstructionWrite.h"
#include "InstructionRead.h"
#include "InstructionHalt.h"
#include "InstructionJmp.h"
#include "InstructionNeg.h"
#include "InstructionAssign.h"
#include "InstructionJmpIf.h"

bool is_digits(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
}

class InstructionFactory
{
    protected:
    
    std::ifstream instfile;

    public:
    InstructionFactory(){};

    ~InstructionFactory() { instfile.close(); };

    int inline ParseFile(std::string filename, int DataMemory[], Instruction** InstructionMemory)
    {
        instfile.open(filename);
        std::string line;
        int i = 0;
        std::string word;
        std::vector<std::string> tokens;
        parameters p;

        while(std::getline(instfile,line))
        {   
            tokens.clear();
            std::istringstream iss(line);
            while(iss >> word)
            {
                tokens.push_back(word);
            }
            
            if(tokens.size() == 1)  {
                //HALT SYSTEM
                if(tokens[0] == "HALT")        /*STOP SYSTEM*/
                        InstructionMemory[i] = new InstructionHalt(new parameters(p));
                else
                    throw -3;
                    }
            else if(tokens.size() == 2) {
                // One Parameter Instructions
                // Parameter Checking

                //CHECKING FIRST PARAMETER
                if(tokens[1].find('x') !=  std::string::npos)          //Check if ADDRESS for first parameter
                    {
                        if(is_digits(tokens[1].substr(tokens[1].find('x')+1,-1)))
                        {
                            p.isp1addr = true;       //IT IS AN ADDRESS
                            if(std::stoi(tokens[1].substr(tokens[1].find('x')+1,-1)) < 1024)
                                  p.p1.param1addr = &DataMemory[std::stoi(tokens[1].substr(tokens[1].find('x')+1,-1))];  //REFERENCE TO ADDRESS IN MEMORY
                            else
                                throw -4;
                        }
                        else
                            throw -2; // Incorrect Parameter Value
                    }
                else if(is_digits(tokens[1]))
                    {
                        p.isp1addr = false;
                        p.p1.param1val = std::stoi(tokens[1]);
                    }
                else
                    throw -2; // Incorrect parameter value      


                if(tokens[0] == "READ") {
                    if(!p.isp1addr)
                        throw -2;
                    else  {
                        InstructionMemory[i] = new InstructionRead(new parameters(p));
                    }
                }
                else if(tokens[0] == "WRITE") {
                    InstructionMemory[i] = new InstructionWrite(new parameters(p));
                }
                else if(tokens[0] == "JMP") {
                    if(p.isp1addr)
                        throw -2;
                    else
                    {
                        InstructionMemory[i] = new InstructionJmp(new parameters(p));
                    }
                }
                else
                    throw -3;   //INCORRECT INSTRUCTION
            }
            else if(tokens.size() == 3) {
                // Two Parameter Instructions
                //Checking FIRST PARAMETER 
                if(tokens[1].find('x') !=  std::string::npos)          //Check if ADDRESS for first parameter
                    {
                        if(is_digits(tokens[1].substr(tokens[1].find('x')+1,-1)))
                        {
                            p.isp1addr = true;       //IT IS AN ADDRESS
                            if(std::stoi(tokens[1].substr(tokens[1].find('x')+1,-1)) < 1024)
                                p.p1.param1addr = &DataMemory[std::stoi(tokens[1].substr(tokens[1].find('x')+1,-1))];  //REFERENCE TO ADDRESS IN MEMORY
                            else
                                    throw -4;
                            
                        }
                        else
                            throw -2; // Incorrect Parameter Value
                    }
                else if(is_digits(tokens[1]))
                    {
                        p.isp1addr = false;
                        p.p1.param1val = std::stoi(tokens[1]);
                    }
                else
                    throw -2; // Incorrect parameter value

                // CHECKING SECOND PARAMETER
                if(tokens[2].find('x') != std::string::npos)          //Check if ADDRESS for first parameter
                    {
                        if(is_digits(tokens[2].substr(tokens[2].find('x')+1,-1)))
                            {
                                p.isp2addr = true;       //IT IS AN ADDRESS
                                if(std::stoi(tokens[2].substr(tokens[2].find('x')+1,-1)) < 1024)
                                   p.p2.param2addr = &DataMemory[std::stoi(tokens[2].substr(tokens[2].find('x')+1,-1))];  //REFERENCE TO ADDRESS IN MEMORY
                                else
                                    throw -4;
                            }
                        else
                            throw -2; //Incorrect parameter value 
                    }
                else if(is_digits(tokens[2]))
                    {
                        p.isp2addr = false;
                        p.p2.param2val = std::stoi(tokens[2]);
                    }
                else
                    throw -2; // Incorrect parameter value
                

                if(tokens[0] == "NEG") {
                    if(!p.isp2addr)
                        throw -2;
                    else
                    {
                        InstructionMemory[i] = new InstructionNeg(new parameters(p));
                    }
                    
                }
                else if(tokens[0] == "JMP0") {
                    if(p.isp2addr)
                        throw -2;
                    else
                    {
                        InstructionMemory[i] = new InstructionJmpif(new parameters(p));
                    }
                    
                }
                else if(tokens[0] == "ASS") {
                    if(!p.isp2addr)
                        throw -2;
                    else
                    {
                        InstructionMemory[i] = new InstructionAssign(new parameters(p));
                    }
                    
                }
                else
                    throw -3; // INCORRECT INSTRUCTION
                
            }
            else if(tokens.size() == 4) {
                // Three Parameter Instructions
                
                //CHECKING FIRST PARAMETER
                if(tokens[1].find('x') !=  std::string::npos)          //Check if ADDRESS for first parameter
                    {
                        if(is_digits(tokens[1].substr(tokens[1].find('x')+1,-1)))
                        {
                            p.isp1addr = true;       //IT IS AN ADDRESS
                            if(std::stoi(tokens[1].substr(tokens[1].find('x')+1,-1)) < 1024)
                                p.p1.param1addr = &DataMemory[std::stoi(tokens[1].substr(tokens[1].find('x')+1,-1))];  //REFERENCE TO ADDRESS IN MEMORY
                            else
                                throw -4;
                        }
                        else
                            throw -2; // Incorrect Parameter Value
                    }
                else if(is_digits(tokens[1]))
                    {
                        p.isp1addr = false;
                        p.p1.param1val = std::stoi(tokens[1]);
                    }
                else
                    throw -2; // Incorrect parameter value

                // CHECKING SECOND PARAMETER
                if(tokens[2].find('x') != std::string::npos)          //Check if ADDRESS for first parameter
                    {
                        if(is_digits(tokens[2].substr(tokens[2].find('x')+1,-1)))
                            {
                                p.isp2addr = true;       //IT IS AN ADDRESS
                                if(std::stoi(tokens[2].substr(tokens[2].find('x')+1,-1)) < 1024)
                                    p.p2.param2addr = &DataMemory[std::stoi(tokens[2].substr(tokens[2].find('x')+1,-1))];  //REFERENCE TO ADDRESS IN MEMORY
                                else
                                    throw -4;
                            }
                        else
                            throw -2; //Incorrect parameter value 
                    }
                else if(is_digits(tokens[2]))
                    {
                        p.isp2addr = false;
                        p.p2.param2val = std::stoi(tokens[2]);
                    }
                else
                    throw -2; // Incorrect parameter value
                
                //CHECKING THIRD PARAMETER ( MUST BE ADDRESS )
                if(tokens[3].find('x') != std::string::npos)          //Check if ADDRESS for third parameter
                    {
                        if(is_digits(tokens[3].substr(tokens[3].find('x')+1,-1)))
                        {
                            p.isp3addr = true;       //IT IS AN ADDRESS
                            if(std::stoi(tokens[3].substr(tokens[3].find('x')+1,-1)) < 1024)
                                p.p3.param3addr = &DataMemory[std::stoi(tokens[3].substr(tokens[3].find('x')+1,-1))];  //REFERENCE TO ADDRESS IN MEMORY
                            else
                                throw -4;
                        }
                        else
                            throw -2;   //Incorrect Parameter Value
                    }
                else 
                    throw -2; // Incorrect parameter value


                if(tokens[0] == "ADD") {
                    InstructionMemory[i] = new InstructionAdd(new parameters(p));
                }
                else if(tokens[0] == "MUL") {
                    InstructionMemory[i] = new InstructionMult(new parameters(p));
                }
                else if(tokens[0] == "LE") {
                    InstructionMemory[i] = new InstructionLE(new parameters(p));
                }
                else 
                    throw -3;     //INCORRECT INSTRUCTION
            }
            else 
                throw -3;            
            
            i++;
        }


		return i;
    }

};

#endif