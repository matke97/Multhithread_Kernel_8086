#ifndef _BLCQ_H_
#define _BLCQ_H_
#include"PCB.h"
class Block{
public:
    Block();
    void putSleep(PCB*,Time);//blokira se proces pozivom sleep metode
    void putWait(PCB*,PCB*);//dodavanje u blok listu waitToComplete()
    void decTime();
    void put(PCB*);
   //void obidji();
  // void checkW();
    PCB* get();
private:
    struct lista{
        volatile PCB* inf;
        volatile lista *next;
        volatile int slpFlag;
        volatile Time slpTime;
        volatile PCB *waiting;
        lista(PCB *p):next(0),slpFlag(0),waiting(0)
        {
            inf=p;
        }
    };
    volatile lista *head,*tail;
};

#endif