#include <kernel/kernel.h>

void kmain(multiboot_info_t* mbi) {
    cls();

    gdt_install();

    printf("[OK] installed  GDT\n"); 

    register_isr(0x10, isr_handler);
    register_isr(0x80, syscall_handler_driver);
    register_isr(0x21, syscall_handler);

    timer_install();

    isr_install();

    printf("[OK] installed ISR\n");

    printf("[Test] interrupt .");

    asm("movl %0, %%eax" : : "r" (42));

    printf(".");

    asm volatile("int $0x80");

    unsigned int blockNumber = 10;
    char buffer[BLOCK_SIZE];

    printf("Block 0: ");
    readBlock(blockNumber, buffer);
    buffer[BLOCK_SIZE - 1] = '\0';  // Nullterminierungszeichen setzen
    printf("%s\n", buffer);

    printf("Write \"Hello\" to Block 0\n");

    memset(buffer, 0, BLOCK_SIZE);
    buffer[0] = 'H';
    buffer[1] = 'e';
    buffer[2] = 'l';
    buffer[3] = 'l';
    buffer[4] = 'o';

    printf("Buffer: \"%s\"\n", buffer);

    writeBlock(blockNumber, buffer);

    printf("Updated Block 0: \"");
    readBlock(blockNumber, buffer);
    buffer[BLOCK_SIZE - 1] = '\0';  // Nullterminierungszeichen setzen
    printf("%s\"\n", buffer);

    printf("PCI");

    uint8_t bus = 0;
    uint8_t slot = 1;
    uint8_t function = 0;
    uint16_t vendor_id;
    uint16_t device_id;

    // Lese Vendor ID und Device ID des PCI-Geräts
    vendor_id = pci_read_config_dword(bus, slot, function, 0x00) & 0xFFFF;
    device_id = pci_read_config_dword(bus, slot, function, 0x00) >> 16;

    printf("Vendor ID: 0x%X\n", vendor_id);
    printf("Device ID: 0x%X\n", device_id);

}
