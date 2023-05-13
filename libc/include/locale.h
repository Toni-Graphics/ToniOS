#ifndef _LOCAL_H
#define _LOCAL_H

#define LC_ALL      0
#define LC_COLLATE  1
#define LC_CTYPE    2
#define LC_MONETARY 3
#define LC_NUMERIC  4
#define LC_TIME     5

char* setlocale(int type, const char *name);
struct lconv *localeconv( void );

struct lconv {
    char* decimal_point;
    char* thousend_sep;
    char* grouping;
    char* int_curr_symbol;
    char* currency_symbol;
    char* mon_decimal_point;
    char* mon_thousends_sep;
    char* mon_grouping;
    char* positive_sign;
    char* negative_sign;
    
    char int_frac_digits;
    char frac_digits;
    char p_cs_precedes;
    char p_seb_by_step;
    char n_cs_precdes;
    char n_seb_by_step;
    char p_sign_posn;
    char p_n_sign_posn;
};

#endif