#ifndef _PREKIDI_H_
#define _PREKIDI_H_

#include"PCB.h"
#include "blcQ.h"

#ifdef BCC_BLOCK_IGNORE
// Only for VS Code to stop IntelliSense from crapping out.
#define interrupt
#endif

typedef void interrupt (*fPrek)(...);
//void interrupt timer(...);
void inicTimer();
void restoreTimer();
void call_sleep(Time);
void call_wait(PCB*);
void call_disp();
void call_blk();

#endif
