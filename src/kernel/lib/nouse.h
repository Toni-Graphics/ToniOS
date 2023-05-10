#ifndef _NOUSE_H
#define _NOUSE_H

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
#endif