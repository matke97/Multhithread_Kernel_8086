#include "kksem.h"
#include "prekidi.h"
#include"manager.h"
KernelSem::KernelSem(int init):value(init){
    blokTh=new Block();
}
int KernelSem::val()const{
    return (int)value;
}
int KernelSem::wait(int toBlock)
{
    
    if(toBlock){
     if((--value)<0)
     {
       
            blokTh->put((PCB*)PCB::running);
             call_blk();
             return 1;
        }

    }
    else{
        if(value<0)return -1;
        value--;
    }

    return 0;
}
void KernelSem::signal(){
    if((++value)>=0)
    {
        PCB* th=blokTh->get();
        if(th!=0)
            ScheduleManager::put(th);
    }
}
KernelSem::~KernelSem(){}