#include "PCB.h"
#include "prekidi.h"
#include"manager.h"
#include<IOSTREAM.H>
PCB::PCB(Thread *nit,unsigned long velSteka,Time vr):vreme(vr),tleft(vr),finished(0),stSize(velSteka)
{
	#ifndef BCC_BLOCK_IGNORE
	asm {
		pushf
		cli
	}
	
	myTh=nit;
	stek=new unsigned[velSteka];
	stek[velSteka-1]=0x200;//psw registar
	stek[velSteka-2]=FP_SEG(adapter);
	stek[velSteka-3]=FP_OFF(adapter);
	sp=FP_OFF(stek+velSteka-12);
	ss=FP_SEG(stek+velSteka-12);
	bp=FP_OFF(stek+velSteka-12);
	finished=0;
	if(vr==0)
		infFlag=1;
	else
		infFlag=0;
	
	asm popf;
	#endif
	
}
PCB::PCB(void (*fun)(),unsigned long st,Time vr)
{
	#ifndef BCC_BLOCK_IGNORE
	asm {
		pushf
		cli
	}
	vreme=vr;
	tleft=vr;
	myTh=0;
	stSize=st;
	stek=new unsigned[stSize];
	stek[stSize-1]=0x200;//psw registar
	stek[stSize-2]=FP_SEG(fun);
	stek[stSize-3]=FP_OFF(fun);
	sp=FP_OFF(stek+stSize-12);
	ss=FP_SEG(stek+stSize-12);
	bp=FP_OFF(stek+stSize-12);
	finished=0;
	if(vr==0)
		infFlag=1;
	else
		infFlag=0;
	asm popf;
	#endif
}
PCB::PCB():sp(0),ss(0),bp(0)
{
	#ifndef BCC_BLOCK_IGNORE
	asm {
		pushf
		cli
	}
	tleft=defaultTimeSlice;
	vreme=defaultTimeSlice;
	infFlag=0;
	finished=0;
	stek=NULL;
	asm popf
	#endif
}

PCB::~PCB() {
	delete stek;
}
void PCB::start()
{
	//printf("\nSTAVLJAM U RED SPREMNIH");
	#ifndef BCC_BLOCK_IGNORE
	asm cli;
	ScheduleManager::put(this);
	numOfThr++;
	asm sti;
	#endif
}
void PCB::sleep(Time timeToSleep)
{
	call_sleep(timeToSleep);
}
void PCB::adapter()
{
	PCB::running->myTh->run();
	#ifndef BCC_BLOCK_IGNORE
	asm pushf;
	asm cli;
	running->finished=1;
	//cout<<"\nPROCES ZAVRSIO!"<<endl;
	asm popf;
	#endif
	call_blk();
}
void PCB::waitToComplete()
{
	if(finished==0)
		call_wait(this);
	
}



