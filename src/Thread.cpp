/*
 * thread.cpp
 *
 *  Created on: Aug 7, 2018
 *      Author: OS1
 */

#include "Thread.h"
#include "PCB.h"
#include "prekidi.h"
void Thread::start()
{
	myPCB->start();
}
Thread::Thread(StackSize stackSize, Time timeSlice){
	myPCB=new PCB(this,stackSize,timeSlice);
}
void Thread::sleep(Time timeToSleep)
{
	PCB::sleep(timeToSleep);
}
void Thread::waitToComplete()
{
	myPCB->waitToComplete();
}
Thread::~Thread()
{
	delete myPCB;
}
void dispatch()
{
	call_disp();
}

