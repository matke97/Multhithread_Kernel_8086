#include "blCQ.h"
#include<STDIO.H>
#include"manager.h"
#include"SCHEDULE.H"
//#include"SCHEDULE.H"
Block::Block():head(0),tail(0){}
void Block::put(PCB* proc)
{
    if(head==0)
    {
        head=tail=new lista(proc);
    }else
    tail=tail->next=new lista(proc);
    //asm popf;
    //#endif;
    //printf("\nu blk red\n");
}
/*void Block::obidji()
{
    #ifndef BCC_BLOCK_IGNORE
    asm cli;
    printf("\nRRRR\n");
    for(lista *pom=(lista*)head;pom;pom=(lista*)pom->next)
    {
        printf("\n%d %d",pom->slpFlag,pom->slpTime);
    }
    printf("\n");
    asm sti;
    #endif

}*/
PCB* Block::get()
{
   if(head!=0){
    PCB* g=(PCB*)head->inf;
    lista *pom=(lista*)head;
    head=head->next;
    if(head==0)tail=0;
   // delete pom;
    return g;
   }
   return 0;
}
void Block::putSleep(PCB* proc,Time slVr)
{
    put(proc);
    tail->slpFlag=1;
    tail->slpTime=slVr;
}
void Block::putWait(PCB* proc,PCB* wait)
{
    put(proc);
    tail->waiting=wait;
}
void Block::decTime()
{
    
    volatile lista *pret=(lista*)head;
    for(volatile lista* pom=head;pom!=0;pom=pom->next)
    {
      
        if(pom->slpFlag==1)
        {
            if(pom->slpTime){pom->slpTime--;}
            
            if(pom->slpTime==0)
            {
                volatile lista *g=pom;
                if(pom!=head){
                    pret->next=g->next;
                    pom=pret;
                }
                else
                {
                   head=g->next;
                   pom=head;
                }
                if(g==tail)
                    tail=pom;
                ScheduleManager::put((PCB*)g->inf);
                g->next=0;
            delete (lista*)g;
            }
        }else if(pom->waiting->finished==1)
        {
             volatile lista *g=pom;
                if(pom!=head){
                    pret->next=pom->next;
                    pom=pret;
                }
                else
                {
                   head=g->next;
                   pom=head;
                }
                if(g==tail)
                    tail=pret;
                ScheduleManager::put((PCB*)g->inf);
                g->next=0;
                delete (lista*)g;
        }
        pret=pom;
    }
}
