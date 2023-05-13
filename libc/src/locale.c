#include <locale.h>

#include <stdlib.h>

struct lconv *locale;

char *setlocale(int type, const char *name) {
    if (type == LC_ALL) {
        if (name == "C") {
            
        }
        else if (name == "") {

        }
        else if (name == NULL) {

        }
    }
    else if (type == LC_COLLATE) {
        if (name == "C") {

        }
        else if (name == "") {

        }
        else if (name == NULL) {

        }
    }
    else if (type == LC_CTYPE) {
        if (name == "C") {

        }
        else if (name == "") {

        }
        else if (name == NULL) {

        }
    }
    else if (type == LC_MONETARY) {
        if (name == "C") {

        }
        else if (name == "") {

        }
        else if (name == NULL) {

        }
    }
    else if (type == LC_NUMERIC) {
        if (name == "C") {

        }
        else if (name == "") {

        }
        else if (name == NULL) {

        }
    }
    else if (type == LC_TIME) {
        if (name == "C") {

        }
        else if (name == "") {

        }
        else if (name == NULL) {

        }
    }
    else 
        return -1;
}

struct lconv *localeconv( void ) {
    return locale;
}