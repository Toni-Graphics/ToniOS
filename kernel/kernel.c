#include <stdio.h>
#include <multiboot.h>
#include <isr/isr.h>
#include <gdt/gdt.h>
#include <x86/x86.h>
#include <fs/fs_low.h>


void kmain(multiboot_info_t* mbi) {
    cls();

    gdt_install();

    printf("[OK] installed  GDT\n"); 

    register_isr(0x80, isr_handler);

    isr_install();

    printf("[OK] installed ISR\n");

    printf("Testing filesystem\n");

    fs_init();

    int blockNumber = 10;
    char buffer[BLOCK_SIZE];

    readBlock(blockNumber, buffer);
    printf("Content of Blocks %d: %s\n", blockNumber, buffer);

    const char *dataToWrite = "This is example Content";
    writeBlock(blockNumber, dataToWrite);
    printf("Block %d overwritten\n", blockNumber);

    readBlock(blockNumber, buffer);
    printf("Overwritten Block %d: %s\n", blockNumber, buffer);

}
