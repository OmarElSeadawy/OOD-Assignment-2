#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include "Parameters.h"
#include <mutex>
#include <iostream>

class Instruction
{
    protected:
    parameters *p;
    
    public:
    Instruction(){}

    int LockMutexes2(parameters *p)
    {
        if(p->p1m == p->p2m)
            {
                std::scoped_lock(*(p->p1m));
                return 0;
            }
        else
            {
                std::scoped_lock(*(p->p1m),*(p->p2m));
                return 2;
            }
    }
    int LockMutexes(parameters *p)
    {

        if((p->p1m == p->p2m)&&(p->p2m == p->p3m))
           {
               //Lock One of them only return 0
               std::scoped_lock(*(p->p1m));
               return 0;
           } 
        else if((p->p1m == p->p2m) && (p->p1m != p->p3m))
           {
                // Lock P1/P2 and P3  return 1
                std::scoped_lock(*(p->p1m),*(p->p3m));
                return 1;
           } 
        else if((p->p1m == p->p3m) && (p->p1m != p->p2m))
           {
               //Lock P1/P3 and P2   return 2
               std::scoped_lock(*(p->p1m),*(p->p2m));
               return 2;
           } 
        else if((p->p2m == p->p3m) && (p->p1m != p->p2m))
           {
               // Lock P1 and P2/P3  return 3
               std::scoped_lock(*(p->p1m),*(p->p2m));
               return 3;
           } 
        else
           {
               // LOCK ALL THREE     return 4
               std::scoped_lock(*(p->p1m),*(p->p2m),*(p->p3m));
               return 4;
           } 
    }

    void UnlockMutexes(parameters *p, int t)
    {

        switch(t)
        {
            case 0:
            p->p1m->unlock();
            break;

            case 1:
            p->p1m->unlock();
            p->p3m->unlock();
            break;

            case 2:
            p->p1m->unlock();
            p->p2m->unlock();
            break;

            case 3:
            p->p1m->unlock();
            p->p2m->unlock();
            break;

            case 4:
            p->p1m->unlock();
            p->p2m->unlock();
            p->p3m->unlock();
            break;

            default:
            break;
        }

    }
    virtual void Execute(int&PC) = 0;
    Instruction(parameters* params):p(params){}
    virtual ~Instruction()
    {
        delete p;
    }
};


#endif