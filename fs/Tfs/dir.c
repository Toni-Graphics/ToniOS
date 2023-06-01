#include "dir.h"
#include "lba.h"
#include <string.h>

DIR mkdir(char* name, char* path) {
    int lba = getLba(path);

    DIR dir;
    dir.lba = lba;
    addFile(&dir, name, DIR_TYPE_DIR);
    return dir;
}

void rmdir(char* name, char* path) {
    int lba = getLba(path);

    DIR dir;
    dir.lba = lba;

    rmFile(&dir, name, DIR_TYPE_DIR);
}

FILE addFile(DIR *directory, char* name, int type) {
    char* buffer;

    FILE dir;
    dir.drive = 0;
    dir.lba = directory->lba;


    read(dir, &buffer);
    memcpy(buffer, &directory, sizeof(directory));

    size_t nr_entrys = sizeof(directory->subs) / sizeof(DIR_ENTRY);

    DIR_ENTRY new[nr_entrys+1];

    for (size_t i=0; i < nr_entrys;i++) {
        DIR_ENTRY entry = directory->subs[i];
        new[i] = directory->subs[i];  
    }

    DIR_ENTRY newD;
    memcpy(name, newD.name, sizeof(newD.name /*256*/ ));

    newD.type = type;
    newD.startBlockNr = getNFBLOCK();

    new[nr_entrys] = newD;

    DIR tmp;
    tmp.lba = directory->lba;
    memcpy(new, tmp.subs, sizeof(new));

    directory = &tmp;

    memset(buffer, 0, sizeof(buffer));

    memcpy(&directory, buffer, sizeof(buffer));

    write(dir, buffer);
}

void rmFile(DIR* directory, char* name, int type) {
    char* buffer;

    FILE dir;
    dir.drive = 0;
    dir.lba = directory->lba;


    read(dir, &buffer);
    memcpy(buffer, &directory, sizeof(directory));

    size_t nr_entrys = sizeof(directory->subs) / sizeof(DIR_ENTRY);

    DIR_ENTRY new[nr_entrys-1];

    for (size_t i=0; i < nr_entrys;i++) {
        DIR_ENTRY entry = directory->subs[i];
        if (entry.name == name && entry.type == type);
        else  
            new[i] = directory->subs[i];  
    }

    DIR tmp;
    tmp.lba = directory->lba;
    memcpy(new, tmp.subs, sizeof(new));

    directory = &tmp;

    memset(buffer, 0, sizeof(buffer));

    memcpy(&directory, buffer, sizeof(buffer));

    write(dir, buffer);
}

DIR_ENTRY* getFiles(DIR *directory) {
    char* buffer;

    FILE dir;
    dir.drive = 0;
    dir.lba = directory->lba;


    read(dir, &buffer);
    memcpy(buffer, &directory, sizeof(directory));

    return directory->subs;
}