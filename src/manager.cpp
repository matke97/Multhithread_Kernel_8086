#include"manager.h"
#include"SCHEDULE.H"
#include<STDIO.H>
#include"blcQ.h"
volatile int PCB::numOfThr;
void idle(){
        #ifndef BCC_BLOCK_IGNORE
    //asm sti;
    while(PCB::numOfThr);
    printf("\nKRKRKRK\n");
    #endif
}
PCB* idNit=new PCB(idle,defaultStackSize,1);

void ScheduleManager::put(PCB* proces)
{
   #ifndef BCC_BLOCK_IGNORE
    asm{
        pushf
        cli
    };
    if(proces!=idNit)
    {
        Scheduler::put(proces);
    }
    asm popf;
    #endif
}
PCB* ScheduleManager::get()
{
     PCB* p;
    p=Scheduler::get();
    if(p)
    {
        return p;
    }else {return idNit;}
    
}
void putThread(PCB *proces)
{
    #ifndef BCC_BLOCK_IGNORE
    asm{
        pushf
        cli
    };
        //                    ((Block*)red)->obidji();

    //printf("\nCCCCC");
    if(proces!=idNit)
    {
        //printf("\nBBBBB .%d %d %d.",proces->ss,proces->sp,proces->bp);
        //printf("\nMECAVAM U RED");

        Scheduler::put(proces);
    }//else printf("\nedddddd");//else idNit=p;
    asm popf;
    #endif
}
PCB* getThread()
{
    PCB* p;
    p=Scheduler::get();
    if(p)
    {
        return p;
    }else {return idNit;}
}