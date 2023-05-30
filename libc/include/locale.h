#ifndef _LOCAL_H
#define _LOCAL_H

#define LC_LANG 0
#define LC_keyL 1

char* setlocale(int type, const char *name);
struct local *localeconv( void );

struct local {
    char* lang;
    char* keyL;
};

#endif