#include <stdlib.h>
#include <stdbool.h>

unsigned long long __udivdi3(unsigned long long num, unsigned long long den) {
    unsigned long long bit = 1;
    unsigned long long res = 0;
    
    while (den <= num) {
        den <<= 1;
        bit <<= 1;
    }
    
    while (bit > 1) {
        den >>= 1;
        bit >>= 1;
        
        if (num >= den) {
            num -= den;
            res |= bit;
        }
    }
    
    return res;
}

unsigned long long __umoddi3(unsigned long long num, unsigned long long den) {
    unsigned long long bit = 1;
    
    while (den <= num) {
        den <<= 1;
        bit <<= 1;
    }
    
    unsigned long long res = 0;
    
    while (bit > 1) {
        den >>= 1;
        bit >>= 1;
        
        if (num >= den) {
            num -= den;
            res |= bit;
        }
    }
    
    return num;
}

void system(char* str) {
    //Handle the str
}

void setBit(char* array, int index, bool value) {
    int byteIndex = index / 8;
    int bitPosition = index % 8;

    char bitmask = 1 << bitPosition;

    if (value) {
        array[byteIndex] |= bitmask;
    } else {
        array[byteIndex] &= ~bitmask;
    }
}

bool getBit(const char* array, int index) {
    int byteIndex = index / 8;
    int bitPosition = index % 8;

    char bitmask = 1 << bitPosition;

    return (array[byteIndex] & bitmask) != 0;
}