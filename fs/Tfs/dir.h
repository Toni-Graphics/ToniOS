#include <stdint.h>
#include "file.h"

#ifndef _DIR_H
#define _DIR_H

#define DIR_TYPE_DIR  0
#define DIR_TYPE_FILE 1

typedef struct {
    char name[256];
    uint32_t startBlockNr;
    uint8_t type;
} DIR_ENTRY;

typedef struct {
    DIR_ENTRY subs[1];
    uint32_t lba;
} DIR;

DIR mkdir(char* name, char* path);
void rmdir(char* name, char* path);

FILE addFile(DIR *directory, char* name, int type);
void rmFile(DIR *directory, char* name, int type);

DIR_ENTRY* getFiles(DIR *directory);

#endif