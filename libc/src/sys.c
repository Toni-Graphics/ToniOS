#include <sys.h>

void execb(void* adr){
     
     __asm__("call %0" :: "m" (adr));
}