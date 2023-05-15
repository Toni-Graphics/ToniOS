#ifndef _ISR_H
#define _ISR_H

void isr_install();

void isr_handler(int i_nr);

void register_isr(int interrupt_number, void (*handler)());

#endif