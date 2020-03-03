#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "PCB.h"
//#include <SCHEDULE.H>

//#include"SCHEDULE.H"

class ScheduleManager{
    public:
    static void put(PCB*);
    static PCB* get();
};
void putThread(PCB*);
PCB* getThread();
#endif
