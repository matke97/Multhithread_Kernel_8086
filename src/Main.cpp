#include "Thread.h"
#include<IOSTREAM.H>
#include<STDIO.H>
#include<STDLIB.H>
#include "prekidi.h"
#include "PCB.h"

extern volatile Block* redSleep;
extern volatile Block* redWait;

extern int user(int argc,char*argv[]);
extern int userMain(int argc, char* argv[]);
int main(int argc, char *argv[])
{
    printf("POCETAK");
    inicSys();
   userMain(argc,argv);
   user(argc,argv);

    restoreTimer();
  cout<<"\nKRAJ PROGRAMA!";
    return 0;
}
void inicSys()
{
    #ifndef BCC_BLOCK_IGNORE
    asm cli;
    #endif
    PCB::running=new PCB(); //glavna nit-pri promeni konteksta ce uzeti vrednosti
	inicTimer();
    redSleep=new Block();
    redWait=new Block();
    PCB::numOfThr=1;
    #ifndef BCC_BLOCK_IGNORE
    asm sti;
    #endif
}