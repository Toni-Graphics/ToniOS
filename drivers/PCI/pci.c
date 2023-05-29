#include <drivers/PCI/pci.h>

void pci_write_config_dword (uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint32_t value){
    uint32_t adress = (1 << 31) | (bus << 16) | (slot << 11) | (func << 8) | (offset & 0xFC);

    outl(PCI_CONFIG_ADRESS, adress);
    outl(PCI_CONFIG_DATA, value);

}
uint32_t pci_read_config_dword(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
    uint32_t adress = (1 << 32) | (bus << 16) | (slot << 11) | (func << 8) | (offset & 0xFC);

    outl(PCI_CONFIG_ADRESS, adress);
    return inl(PCI_CONFIG_DATA);

}