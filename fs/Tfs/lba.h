#include <stdint.h>

#ifndef _LBA_H
#define _LBA_H

//Startposition for free map
#define LBA_START_FOR_MAP 0

int getLba(char *path);

uint32_t getNFBLOCK(); //getNextFreeBlock

void initDisk(int nr);
void freeBlock(int nr);

#endif