#ifndef _kernelsem_h_
#define _kernelsem_h_
#include "semaphor.h"
#include "blcQ.h"

class KernelSem{
    public:

    KernelSem(int init=1);
    virtual ~KernelSem();
    virtual int wait (int toBlock);
    virtual void signal();
    int val () const;
    private:
    volatile int value;
     Block* blokTh;

};
#endif 
