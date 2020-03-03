#include"KernelEv.h"
#include"IVTEntry.h"
IvtEntry::IvtEntry(fPrek ff,IVTNo br)
    {
        rutine[br]=ff;
    }
void IvtEntry::getStara(fPrek old,IVTNo br)
    {
        old=dog[br]->oldRtn;
    }
void IvtEntry::signal(IVTNo br)
    {
        dog[br]->signal();
    }