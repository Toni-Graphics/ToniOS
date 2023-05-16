#include <stdio.h>
#include <drivers/io.h>
#include <fs/fs_low.h>
#include <stdint.h>

void readBlock(int blockNumber, char *buffer) {
    unsigned int lba = blockNumber * (BLOCK_SIZE / 2);

    //while ((inb(STATUS_COMMAND_REGISTER) & 0x80) != 0);

    outb(0xE0 | ((lba >> 24) & 0xF), STATUS_COMMAND_REGISTER); 
    outb(lba & 0xFF, STATUS_COMMAND_REGISTER + 1); 
    outb((lba >> 8) & 0xFF, STATUS_COMMAND_REGISTER + 2); 
    outb((lba >> 16) & 0xFF, STATUS_COMMAND_REGISTER + 3); 
    outb(0x20, STATUS_COMMAND_REGISTER + 4);


    //while ((inb(STATUS_COMMAND_REGISTER) & 0x40) == 0);

    insw(DATA_REGISTER, buffer, BLOCK_SIZE / 2);
}

void writeBlock(int blockNumber, const char *buffer) {
    unsigned int lba = blockNumber * (BLOCK_SIZE / 2);

    //while ((inb(STATUS_COMMAND_REGISTER) & 0x80) != 0);

    outb(0xE0 | ((lba >> 24) & 0xF), STATUS_COMMAND_REGISTER); 
    outb(lba & 0xFF, STATUS_COMMAND_REGISTER + 1);
    outb((lba >> 8) & 0xFF, STATUS_COMMAND_REGISTER + 2);
    outb((lba >> 16) & 0xFF, STATUS_COMMAND_REGISTER + 3);
    outb(0x30, STATUS_COMMAND_REGISTER + 4); 

    //while ((inb(STATUS_COMMAND_REGISTER) & 0x8) == 0);

    outsw(DATA_REGISTER, buffer, BLOCK_SIZE / 2);
}

void fs_init() {
    //while ((inb(STATUS_COMMAND_REGISTER) & 0x40) != 0x40);

    outb(CMD_IDENTIFY_DRIVE, STATUS_COMMAND_REGISTER);

    //while ((inb(STATUS_COMMAND_REGISTER) & 0x40) != 0x40);

    uint8_t status = inb(STATUS_COMMAND_REGISTER);
    if (status & 0x01) {
        printf("Fehler beim Lesen der Festplattenidentifikation!\n");
        return;
    }
    //while ((inb(STATUS_COMMAND_REGISTER) & 0x40) != 0x40);

    outb(CMD_SET_FEATURES, STATUS_COMMAND_REGISTER);
    outb(0x03, ERROR_FEATURE_REGISTER);

    //while ((inb(STATUS_COMMAND_REGISTER) & 0x40) != 0x40);

    outb(CMD_SET_FEATURES, STATUS_COMMAND_REGISTER);
    outb(0x200 >> 8, ERROR_FEATURE_REGISTER);
    outb(0x200 & 0xFF, ERROR_FEATURE_REGISTER);
}