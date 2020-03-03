#include "prekidi.h"
//#include"SCHEDULE.H"
#include"manager.h"
#include<STDIO.H>

volatile int Flag=0;//flag:1-dispach;2-sleep,3-waitToCompl
volatile PCB* PCB::running;
fPrek stara;
extern void tick();
extern volatile PCB* idNit;
volatile Block* redSleep;
volatile Block* redWait;
volatile unsigned tsp,tss,tbp;
volatile Time tsleep;
volatile PCB* wBlkNit;
void call_sleep(Time tslp){

	#ifndef BCC_BLOCK_IGNORE
	asm{
		pushf
		cli
	}
	Flag=2;
	tsleep=tslp;
	asm popf;
	asm int 08h;
	#endif
}
void call_wait(PCB* nit){
	#ifndef BCC_BLOCK_IGNORE
	asm{
		pushf
		cli
	} 
	Flag=3;
	wBlkNit=nit;
	asm popf;
	asm int 08h;
	#endif
}
void call_disp(){
	#ifndef BCC_BLOCK_IGNORE
	asm pushf;
	asm cli;
	Flag=1;
	asm popf;
	asm int 08h;
	#endif
}
void call_blk() //samo menja kontekst,a pozivajucu nit ne stavlja ni u red spremnih,ni u red blokiranih
{
	#ifndef BCC_BLOCK_IGNORE
	asm pushf;
	asm cli;
	Flag=4;
	asm popf;
	asm int 08h;
	#endif

}
void interrupt timer(...)
{   
	if(!Flag){
		//printf("\nTIK TIMERA %d %d",PCB::running->tleft, PCB::running->infFlag);
		if(PCB::running->infFlag==0)
		{
			
				PCB::running->tleft=PCB::running->tleft-1;
			//printf("\nSMANJUJEM");
		}
		//((Block*)red)->obidji();
		((Block*)redSleep)->decTime();
		((Block*)redWait)->decTime();
		//printf("\nPOSLE");
		//((Block*)red)->obidji();
				//printf("\n22222TIK TIMERA %d %d",PCB::running->tleft, PCB::running->infFlag);

	}
	//printf("\nvr=%d\n",PCB::running->tleft);
	
	if((PCB::running->tleft==0 && !PCB::running->infFlag)|| Flag!=0)
	{
        //printf("\nISPOD IFA");
		#ifndef BCC_BLOCK_IGNORE
		asm{
			mov tsp,sp
			mov tss,ss
			mov tbp,bp
		}
		#endif
		if(!Flag){PCB::running->tleft=PCB::running->vreme;}
		PCB::running->bp=tbp;
		PCB::running->sp=tsp;
		PCB::running->ss=tss;
		//printf("\nAAA%d %d %d",tbp,tsp,tss);
		switch(Flag)
		{
			case 0:
			case 1:
			//if(PCB::running!=idNit)
				ScheduleManager::put((PCB*)PCB::running);
				//else idNit=PCB::running; //cuva trenutni kontekst
			break;
			case 2:
			//printf("\nCCCCC .%d %d %d.",PCB::running->ss,PCB::running->sp,PCB::running->bp);

			((Block*)redSleep)->putSleep((PCB*)PCB::running,tsleep);
			break;
			case 3:
			((Block*)redWait)->putWait((PCB*)PCB::running,(PCB*)wBlkNit);
			break;
			case 4:break;
		}
		
		PCB::running=ScheduleManager::get();

		tsp=PCB::running->sp;
		tss=PCB::running->ss;
		tbp=PCB::running->bp;
		//printf("\nBBB%d\n%d\n%d\nVREME=%d\n",tbp,tsp,tss,PCB::running->tleft);
		#ifndef BCC_BLOCK_IGNORE
		asm{
			mov sp,tsp
			mov ss,tss
			mov bp,tbp
		}
		#endif
	}
	#ifndef BCC_BLOCK_IGNORE
	if(!Flag){
		tick();
		asm int 60h;
	}else
    	Flag=0;
	#endif
}

void inicTimer()
{
	//podesiti nas timer na 08h a ovu na 60h
	#ifndef BCC_BLOCK_IGNORE
	asm cli;
	
	
	stara=getvect(0x08);
	setvect(0x08,timer);
	setvect(0x60,stara);
	asm sti;
	#endif
	
}
void restoreTimer()
{
	#ifndef BCC_BLOCK_IGNORE
	asm cli;
	setvect(0x08,stara);
	asm sti;
	#endif
}