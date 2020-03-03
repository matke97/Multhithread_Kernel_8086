#ifndef _IVTENTRY_H_
#define _IVTENTRY_H_
//#include"KernelEv.h"
#ifndef  BCC_BLOCK_IGNORE
//#define interrupt
typedef void interrupt (*fPrek)(...);

#endif

typedef unsigned char IVTNo;
class KernelEv;

class IvtEntry{
    public:
    static KernelEv* dog[256];
    static fPrek rutine[256];
    IvtEntry(fPrek ff,IVTNo br);
    static void getStara(fPrek old,IVTNo br);
    static void signal(IVTNo br);
};
#define PREPAREENTRY(ivtNo, callOld)\
	KernelEv* IvtEntry::dog[256];\
	void interrupt intr##ivtNo() {\
		fPrek old;\
		IvtEntry::getStara(old, ivtNo);\
		IvtEntry::signal(ivtNo);\
		if (callOld) {\
			old();\
		}\
	}\
	IvtEntry Instance##ivtNo((fPrek) intr##ivtNo, (IVTNo) ivtNo);\

#endif
