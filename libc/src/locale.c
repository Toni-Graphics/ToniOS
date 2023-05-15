#include <locale.h>

#include <stdlib.h>

struct local *locale;

char *setlocale(int type, const char *name) {
    if (type == LC_LANG)
        locale->lang = name;
    else if (type == LC_keyL)
        locale->keyL = name;
}

struct local *localeconv( void ) {
    return locale;
}