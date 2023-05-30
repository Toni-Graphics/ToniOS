#include <timer/timer.h>

int t_ticks = 0;
int seconds = 0;

void timer_handler(void) {
    t_ticks++;

    if (t_ticks % 18 == 0)
        seconds++;
}

void timer_phase(int hz) {
    int div = 1193180 / hz;
    outb(0x43, 0x36);
    outb(0x40, div & 0xff);
    outb(0x40, div >> 8);
}

void timer_install()     {
    register_isr(0, timer_handler);
}

int sleep(int ticks)    {
    int sTicks = t_ticks;

    printf("Start ticks %d\n", sTicks);
    printf("End ticks %d\n", sTicks + ticks);

    while (t_ticks < (sTicks + ticks) ) {
    }
    
    printf("Finish sleeping\n");

    return 0;
}