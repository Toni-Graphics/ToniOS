#include "lba.h"
#include <ata/ata.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dir.h"

int getLba(char *path) {

    if (path == "/") {
        return LBA_FS_SUPER;
    }

    else {  //Normal path
        int lba = LBA_FS_SUPER;

        char* subDir;
        char ch;
        DIR acDir;
        acDir.lba = lba;
        DIR_ENTRY* entrys = getFiles(&acDir);

        for (size_t i=0; i < strlen(path); i++) {
            ch = path[i];
            if (ch == '/') { //new dir
                for (size_t x=0; x < ( sizeof(entrys) / sizeof(DIR_ENTRY) ); x++) {
                    DIR_ENTRY entry = entrys[x];
                    if (entry.name == subDir) {
                        acDir.lba = entry.startBlockNr;
                    }
                }
                entrys = getFiles(&acDir);
                memset(subDir, 0, sizeof(subDir));
            }
            else {
                char newStr[sizeof(subDir)+1];
                strcpy(newStr, subDir);
                newStr[sizeof(subDir)] = ch;
            }   
        }

        //subDir is now the filename
        size_t fileIndex = -1;

        for (size_t i=0; i < ( sizeof(entrys) / sizeof(DIR_ENTRY) ); i++) {
            if (entrys[i].name ==  subDir)  {
                fileIndex = i;
                break;
            }
        }   
    }
    return 0;
}

int disk_nr=0;
int nr_sectors=0;

void initDisk(int nr) {
    IDE_DEVICE device = getDevices()[nr];

    disk_nr = nr;

    nr_sectors = device.size / ATA_SECTOR_SIZE;
    char Sec_Map[nr_sectors/8];
    int nr_sectors_for_map = ((nr_sectors/8) / ATA_SECTOR_SIZE) + 1;

    ide_read_sectors(nr, nr_sectors_for_map, LBA_START_FOR_MAP, (uint32_t)Sec_Map);

    bool inited = false;

    if (getBit(Sec_Map, LBA_START_FOR_MAP))
        inited = true;

    if (!inited) {
        memset(Sec_Map, 0, sizeof(Sec_Map));

        for (size_t i=0; i <nr_sectors_for_map; i++) {
            setBit(Sec_Map, LBA_START_FOR_MAP+i, true);
        }

        ide_write_sectors(nr, nr_sectors_for_map, LBA_START_FOR_MAP, (uint32_t)Sec_Map);
    }
}

uint32_t getNFBLOCK() { //getNextFreeBlock
    char Sec_Map[nr_sectors/8];

    int nr_sectors_for_map = ((nr_sectors/8) / ATA_SECTOR_SIZE) + 1;

    ide_read_sectors(disk_nr, nr_sectors_for_map, 
        LBA_START_FOR_MAP, (uint32_t)Sec_Map);

    uint32_t result;

    for (size_t i=0; i < sizeof(Sec_Map); i++) {
        if (getBit(Sec_Map, i)) {
            result = i;
            setBit(Sec_Map, i, true);
            break;            
        }
    }

    return result;

}

void freeBlock(int nr) {
    char Sec_Map[nr_sectors/8];

    int nr_sectors_for_map = ((nr_sectors/8) / ATA_SECTOR_SIZE) + 1;

    ide_read_sectors(disk_nr, nr_sectors_for_map, 
        LBA_START_FOR_MAP, (uint32_t)Sec_Map);

    setBit(Sec_Map, nr, false);

    ide_write_sectors(disk_nr, nr_sectors_for_map,
        LBA_START_FOR_MAP, (uint32_t)Sec_Map);
}