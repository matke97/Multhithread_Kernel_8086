#ifndef _event_h_
#define _event_h_
#include"IVTEntry.h"
//class IVTEntry;
class KernelEv;
typedef unsigned char IVTNo;
/*#ifdef BCC_BLOCK_IGNORE
// Only for VS Code to stop IntelliSense from crapping out.
#define interrupt
#endif
typedef void interrupt (*fPrek)(...);*/

class Event {
public:
Event (IVTNo ivtNo);
~Event ();
void wait ();
protected:
friend class KernelEv;
void signal(); // can call KernelEv
private:
KernelEv* myImpl;
};

#endif