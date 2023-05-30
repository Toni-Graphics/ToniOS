#include "file.h"
#include "lba.h"

FILE open(const int DRIVE, char* path) {
    FILE ret;

    ret.path = path;
    ret.lba = getLba(path);
    ret.drive = DRIVE;

    return ret;
}


int write(FILE handler, char* buffer) {
    size_t block;

    size_t chunkSize = (sizeof(_raw_file) - sizeof(uint32_t));

    size_t strLength = strlen(buffer);
    size_t numChunks = (strLength + chunkSize - 1) / chunkSize; 

    for (size_t i = 0; i < numChunks; i++) {
        char* chunkStart = buffer + i * chunkSize; 
    
       _raw_file raw;

        size_t chunkLength = chunkSize;
        if (i == numChunks - 1) {
            chunkLength = strLength - i * chunkSize; 
            raw.nextBlock = 0;
        }
        else
            raw.nextBlock = getNFBLOCK();

        strcpy(raw.content, chunkStart);

        write_t(handler, raw);
        handler.lba = raw.nextBlock;
    }

}
int read(FILE handler, char** buffer) {
    size_t block;

    while (1) {
        _raw_file con;
        read_t(handler, &con);
        strcpy(buffer, strcat(buffer, con.content));

        if (con.nextBlock == 0)
            break;

    }
    strcpy(buffer, strcat(buffer, '\0'));
    return 0;
}

void write_t(FILE handler, _raw_file raw) {
    char buf[ATA_SECTOR_SIZE];
    memcpy(raw.content, buf, sizeof(raw.content));

    ide_write_sectors(handler.drive, 1, handler.lba, (uint32_t)buf);
}

void read_t(FILE handler, _raw_file* raw) {
    char buf[ATA_SECTOR_SIZE];

    ide_read_sectors(handler.drive, 1, handler.lba, (uint32_t)buf);

    memcpy(buf, raw->content, sizeof(raw->content));

    handler.lba = raw->nextBlock;

}