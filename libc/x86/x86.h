#include <stdbool.h>
#include <stdint.h>

#ifndef _X86_H
#define _X86_h

/*bool __attribute__((cdecl)) x86_Disk_Read(uint8_t drive,
                           uint16_t cylinder,
                           uint16_t sector,
                           uint16_t head,
                           uint8_t count,
                           void* lowerDataOut);*/

void sti();
void cli();

#endif