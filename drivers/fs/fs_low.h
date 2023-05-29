#ifndef _FS_LOWLEVEL_H
#define _FS_LOWLEVEL_H

#define BLOCK_SIZE 512

void readBlock(int blockNumber, char* buffer);
void writeBlock(int blockNumber, const char* data);

#endif