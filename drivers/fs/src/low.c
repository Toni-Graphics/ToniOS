#include <stdio.h>

#define BLOCK_SIZE 512

void readBlock(unsigned int blockNumber, void* buffer) {
    unsigned int portBase = 0x1F0;  // Beispiel: Basisadresse des primären IDE-Controllers
    unsigned int portData = portBase + 0;
    unsigned int portStatus = portBase + 7;
    
    // Warten, bis das Laufwerk bereit ist
    while ((inb(portStatus) & 0x40) != 0x40);
    
    // Blocknummer und Sektoranzahl schreiben
    outb(0x01, portBase + 6);  // LBA-Modus, Bit 6 setzen
    outb((blockNumber >> 24) & 0xFF, portBase + 2);  // Bits 31-24
    outb((blockNumber >> 16) & 0xFF, portBase + 3);  // Bits 23-16
    outb((blockNumber >> 8) & 0xFF, portBase + 4);   // Bits 15-8
    outb(blockNumber & 0xFF, portBase + 5);          // Bits 7-0
    outb(0x01, portBase + 7);  // Lesebefehl senden (CMD READ SECTORS)
    
    // Warten, bis das Laufwerk bereit ist
    while ((inb(portStatus) & 0x40) != 0x40);
    
    // Datenblock lesen
    for (int i = 0; i < BLOCK_SIZE / 2; i++) {
        unsigned short data = inw(portData);
        ((unsigned short*)buffer)[i] = data;
    }
}

void writeBlock(unsigned int blockNumber, const void* buffer) {
    unsigned int portBase = 0x1F0;  // Beispiel: Basisadresse des primären IDE-Controllers
    unsigned int portData = portBase + 0;
    unsigned int portStatus = portBase + 7;
    
    // Warten, bis das Laufwerk bereit ist
    while ((inb(portStatus) & 0x40) != 0x40);
    
    // Blocknummer und Sektoranzahl schreiben
    outb(0x01, portBase + 6);  // LBA-Modus, Bit 6 setzen
    outb((blockNumber >> 24) & 0xFF, portBase + 2);  // Bits 31-24
    outb((blockNumber >> 16) & 0xFF, portBase + 3);  // Bits 23-16
    outb((blockNumber >> 8) & 0xFF, portBase + 4);   // Bits 15-8
    outb(blockNumber & 0xFF, portBase + 5);          // Bits 7-0
    outb(0x30, portBase + 7);  // Schreibbefehl senden (CMD WRITE SECTORS)
    
    // Warten, bis das Laufwerk bereit ist
    while ((inb(portStatus) & 0x40) != 0x40);
    
    // Datenblock schreiben
    for (int i = 0; i < BLOCK_SIZE / 2; i++) {
        unsigned short data = ((const unsigned short*)buffer)[i];
        outw(data, portData);
    }
}
