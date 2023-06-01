#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <drivers/ata/ata.h>

#ifndef _FILE_H
#define _FILE_H

typedef  struct {
    char *path;      //path
    int lba;    //Adress of node
    int drive;
} FILE;

typedef struct {
    uint32_t nextBlock;
    char content[ATA_SECTOR_SIZE - sizeof(uint32_t)];
} _raw_file;

FILE open(char* path);

int write(FILE handler, char* buffer);
int read(FILE handler, char** buffer);

void write_t(FILE handler, _raw_file content);
void read_t(FILE handler, _raw_file* content);

#endif