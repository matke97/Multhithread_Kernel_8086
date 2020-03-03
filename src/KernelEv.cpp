
#include"KernelEv.h"
#include"prekidi.h"
#include"IVTEntry.h"
//#include"SCHEDULE.H"
#include"manager.h"
#include<DOS.H>
fPrek IvtEntry::rutine[256];
//KernelEv* IvtEntry::dog[256];
//volatile PCB* PCB::running;
KernelEv::KernelEv(IVTNo br):evtNum(br)
{
    created=(PCB*)PCB::running;
    IvtEntry::dog[br]=this;
    inicEv();

}
void KernelEv::inicEv()
{
    #ifndef BCC_BLOCK_IGNORE
    asm pushf;
    asm cli;
    oldRtn=getvect(evtNum);
    setvect(evtNum,IvtEntry::rutine[evtNum]);
    asm popf;
    #endif
}
void KernelEv::restore()
{
    #ifndef BCC_BLOCK_IGNORE
    asm pushf;
    asm cli;
    IvtEntry::dog[evtNum]=0;
    setvect(evtNum,oldRtn);
    asm popf;
    #endif
}
KernelEv::~KernelEv()
{
    restore();
}
void KernelEv::wait()
{
    if(created==PCB::running)
    {
        call_blk(); 
    }
}
void KernelEv::signal()
{
    ScheduleManager::put(created);
}