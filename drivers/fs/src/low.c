#include <stdio.h>
#include <drivers/io.h>
#include <fs_low.h>
#include <stdint.h>

void readBlock(int blockNumber, char* buffer) {
    unsigned int blockAddress = blockNumber * BLOCK_SIZE;

    // Read block data from the port in 16-bit chunks
    for (int i = 0; i < BLOCK_SIZE / 2; i++) {
        unsigned int address = blockAddress + (i * 2);
        outw(FS_PORT, address);  // Send the address to the controller
        unsigned short data = inw(FS_PORT);  // Read the block data
        buffer[i * 2] = (char)(data & 0xFF);
        buffer[i * 2 + 1] = (char)((data >> 8) & 0xFF);
    }
}

void writeBlock(int blockNumber, const char* data) {
    unsigned int blockAddress = blockNumber * BLOCK_SIZE;

    // Write block data to the port in 16-bit chunks
    for (int i = 0; i < BLOCK_SIZE / 2; i++) {
        unsigned int address = blockAddress + (i * 2);
        outw(FS_PORT, address);  // Send the address to the controller
        unsigned short blockData = (unsigned short)(data[i * 2] & 0xFF) | ((unsigned short)(data[i * 2 + 1] & 0xFF) << 8);
        outw(FS_PORT, blockData);  // Write the block data
    }

}