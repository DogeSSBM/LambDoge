#ifndef TYPES_H
#define TYPES_H

typedef unsigned int uint;
typedef FILE File;

struct Lst;

typedef enum{T_NAT, T_SYM, T_LST}Type;
const char *TypeStr[] = {"T_NAT", "T_SYM", "T_LST"};

typedef struct{
    char *name;
    struct Lst *args;
    struct Lst*(*fun)(struct Lst*);
}Sym;

typedef struct Lst{
    Type type;
    union{
        uint nat;
        Sym sym;
        struct Lst *lst;
    };
    struct Lst *nxt;
}Lst;

typedef enum{
    P_TYPE  = 1,
    P_LVL   = 1<<1,
    P_POS   = 1<<2,
    P_VAL   = 1<<3,
    P_IND   = 1<<4,
    P_NL    = 1<<5,
    P_ALL   = 1023
}PrintFlags;

Lst* env = NULL;
#endif /* end of include guard: TYPES_H */
