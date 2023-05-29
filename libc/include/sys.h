#ifndef _SYS_H
#define _SYS_H

#define PM_COMMAND 0x64
#define PM_DATA 0x60

// Power management commands
#define PM_CMD_SHUTDOWN 0xF
#define PM_CMD_REBOOT 0xFE

void execb(void* adr);
void restart();
void shutdown();

#endif