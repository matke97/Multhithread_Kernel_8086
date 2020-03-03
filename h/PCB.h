/*
 * PCB.h
 *
 *  Created on: Aug 7, 2018
 *      Author: Milos Matic
 */

#ifndef _PCB_H_
#define _PCB_H_
#include "Thread.h"
#include<DOS.H>
//#include "SCHEDULE.H"
class PCB {
public:
	PCB(Thread*t,unsigned long st=defaultStackSize,Time vr=defaultTimeSlice);
	PCB();//za main
	PCB(void (*fun)(),unsigned long st=defaultStackSize,Time vr=defaultTimeSlice);
	virtual ~PCB();
	static volatile  PCB* running;
	static volatile int numOfThr;
	void start();
	static void sleep(Time timeToSleep);
	void waitToComplete();
	static void adapter();

//private:
	volatile int finished;
	volatile int infFlag;//Ako nije dodeljeno odredjeno vreme,vec nit uzima CPU dok ne zavrsi
	volatile Time vreme,tleft;
	volatile unsigned sp,ss,bp;
	StackSize stSize;
	Thread *myTh;
	private:
	unsigned *stek;//da moze da se oslobodi memorija u destruktoru
}; 

void inicSys();

#endif /* PCB_H_ */
