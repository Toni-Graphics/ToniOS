#include <stdint.h>

#ifndef _PCI_H
#define _PCI_H

#define PCI_CONFIG_ADRESS 0xCF8
#define PCI_CONFIG_DATA    0xCFC

uint32_t pci_read_config_dword(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
void pci_write_config_dword (uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset, uint32_t value);

#endif