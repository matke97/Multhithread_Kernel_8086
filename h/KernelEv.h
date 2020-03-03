#ifndef _KERNELEV_H_
#define _KERNELEV_H_
#include "event.h"
#include "PCB.h"
//#include"IVTEntry.h"
#ifdef BCC_BLOCK_IGNORE
// Only for VS Code to stop IntelliSense from crapping out.
#define interrupt
#endif
typedef void interrupt (*fPrek)(...);

typedef unsigned char IVTNo;

class KernelEv{
    public:
    KernelEv(IVTNo br);
    ~KernelEv();
    void wait();
    void signal();
    fPrek oldRtn;
    private:
    void restore();
    void inicEv();

    PCB* created;
    IVTNo evtNum;
};

#endif