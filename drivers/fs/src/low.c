#include <stdio.h>
#include <drivers/io.h>
#include <fs_low.h>
#include <stdint.h>

void readBlock(int blockNumber, char* buffer) {
    for (int i = 0; i < BLOCK_SIZE / 2; i++) {
        buffer[i] = inw(FS_PORT);
    }
}

void writeBlock(int blockNumber, const char* data) {

    // Write block data to the port in 16-bit chunks
    for (int i = 0; i < BLOCK_SIZE / 2; i++) {
        unsigned short blockData = (unsigned short)(data[i * 2] & 0xFF) | ((unsigned short)(data[i * 2 + 1] & 0xFF) << 8);
        outw(FS_PORT, blockData);
    }
}