#include <stdbool.h>

#ifndef _STDLIB_H
#define _STDLIB_H

#define NULL 0

unsigned long long __udivdi3(unsigned long long num, unsigned long long den); 
unsigned long long __umoddi3(unsigned long long num, unsigned long long den);

void system(char* str);

void setBit(char* array, int index, bool value);
bool getBit(const char* array, int index);

#endif