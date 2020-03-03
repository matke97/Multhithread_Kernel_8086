#include"semaphor.h"
#include"kksem.h"
Semaphore::Semaphore(int init)
{
    myImpl=new KernelSem(init);
}
Semaphore::~Semaphore (){
    delete myImpl;
}
int Semaphore::wait (int toBlock){
    #ifndef BCC_BLOCK_IGNORE
    asm{
        pushf
        cli
    }
    
   int val= myImpl->wait(toBlock);
    asm popf;
    return val;
    #endif
    
}
void Semaphore::signal(){
    #ifndef BCC_BLOCK_IGNORE
    asm{
        pushf
        cli
    }
   
    myImpl->signal();
    asm popf;
     #endif
}
int Semaphore::val () const{
    return myImpl->val();
} // Returns the current value of the semaphore
