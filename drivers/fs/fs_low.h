#ifndef _FS_LOWLEVEL_H
#define _FS_LOWLEVEL_H

#define DATA_REGISTER 0x1F0

#define ERROR_FEATURE_REGISTER 0x1F1
#define SECTOR_COUNT_REGISTER  0x1F2
#define LBA_LOW_REGISTER       0x1F3
#define LBA_MID_REGISTER       0x1F4
#define LBA_HIGH_REGISTER      0x1F5
#define DRIVE_SELECT_REGISTER  0x1F6
#define STATUS_COMMAND_REGISTER 0x1F7

#define CMD_IDENTIFY_DRIVE     0xEC
#define CMD_SET_FEATURES       0xEF
#define CMD_READ_SECTORS_EXT   0x24
#define CMD_WRITE_SECTORS_EXT  0x34

#define BLOCK_SIZE 512

void readBlock(int blockNumber, char* buffer);
void writeBlock(int blockNumber, const char* data);
void fs_init();

#endif