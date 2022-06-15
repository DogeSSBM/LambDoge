#ifndef TYPES_H
#define TYPES_H

typedef unsigned int uint;

typedef enum{T_NAT, T_SYM, T_LST}Type;

typedef struct Lst{
    Type type;
    union{
        uint nat;
        char *sym;
        struct Lst *lst;
    };
    struct Lst *nxt;
}Lst;

#endif /* end of include guard: TYPES_H */
