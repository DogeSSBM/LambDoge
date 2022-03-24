#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef enum{T_NAT, T_SYM, T_LST, T_NIL, T_ERR}Type;

typedef struct Lst{
    Type type;
    union{
        uint nat;
        char *sym;
        struct Lst *lst;
    };
    struct Lst *nxt;
}Lst;

void showErr(char *in, char *err)
{
    const uint len = err-in;
    printf("%s\n", in);
    for(uint i = 0; i < len; i++)
        printf(" ");
    printf("^\n");
}

// ensures input parens are properly formatted and balanced
void checkIn(char *in)
{
    char *pos = in;
    int bal = 0;
    char *last;
    while((pos = strpbrk(pos, "()"))){
        if(bal == 0)
            last = pos;
        if(*pos=='(')
            bal++;
        else
            bal--;
        if(bal < 0){
            fprintf(stderr, "Unexpected ')' at \"%s\"\n", pos);
            showErr(in, pos);
            exit(-1);
        }
        pos++;
    }
    // parens balanced
    if(bal == 0)
        return;
    fprintf(stderr, "Unclosed '(' at \"%s\"\n", last);
    showErr(in, last);
    exit(-1);
}

Type getType(const char c)
{
    if(isdigit(c))
        return T_NAT;
    if(isalpha(c))
        return T_SYM;
    if(c == '(')
        return T_LST;
    if(c == ')')
        return T_NIL;
    return T_ERR;
}

char* skipSpace(char *in)
{
    while(in != NULL && isspace(*in))
        in++;
    return in;
}

uint shiftDigit(uint digit, const uint pos)
{
    for(uint i = 1; i < pos; i++)
        digit *= 10;
    return digit;
}

char *readNat(uint *nat, char *in)
{
    *nat = 0;
    char *end = in;
    while(isdigit(*end))
        end++;
    while(in != end){
        *nat += shiftDigit(*in, end-in);
        in++;
    }
    return skipSpace(in);
}

char *readSym(char **sym, char *in)
{
    char *end = in;
    while(isalpha(*end))
        end++;
    *sym = calloc((end-in)+1, sizeof(char));
    memcpy(*sym, in, end-in);
    return skipSpace(end);
}

char *readLst(Lst **tail, char *in)
{
    Lst *lst = *tail;
    while(in != NULL && *in != '\0'){
        switch(lst->type = getType(*(in = skipSpace(in)))){
            case T_LST:
                lst->lst = calloc(1, sizeof(Lst));
                in++;
                in = readLst(&lst->lst, in);
                break;
            case T_NAT:
                in = readNat(&lst->nat, in);
                break;
            case T_SYM:
                in = readSym(&lst->sym, in);
                break;
            case T_NIL:
                return skipSpace(in+1);
            case T_ERR:
            default:
                fprintf(stderr, "Unknown type starting at \"%s\"\n", in);
                exit(-1);
        }
        lst->nxt = calloc(1, sizeof(Lst));
        skipSpace(in);
        lst = lst->nxt;
    }
    return NULL;
}

Lst *readAll(char *pos)
{
    Lst *lst = calloc(1, sizeof(Lst));
    Lst **all = &lst;
    while((pos = readLst(all, pos)) != NULL && *pos != '0' && (*all)->nxt->type != T_NIL);
    return lst;
}

void ind(const uint lvl)
{
    for(uint i = 0; i < lvl; i++)
        printf("\t");
}

void printLst(Lst *lst)
{
    static uint lvl = 0;
    while(lst){
        switch(lst->type){
            case T_LST:
                ind(lvl);
                printf("(\n");
                lvl++;
                printLst(lst->lst);
                break;
            case T_NAT:
                ind(lvl);
                printf("T_NAT: %u\n", lst->nat);
                lst = lst->nxt;
                break;
            case T_SYM:
                ind(lvl);
                printf("T_SYM: %s\n", lst->sym);
                lst = lst->nxt;
                break;
            case T_NIL:
                lvl--;
                ind(lvl);
                printf("(\n");
                return;
                break;
            case T_ERR:
            default:
                ind(lvl);
                fprintf(stderr, "T_ERR: printing is borked\n");
                exit(-1);
                break;
        }
        lst = lst->nxt;
    }
}

int main(int argc, char *argv[])
{
    if(argc != 2){
        fprintf(stderr, "Usage:\n%s \"<Input Lst>\"\n\n", argv[0]);
        fprintf(stderr, "Example:\n%s \"()\"\n", argv[0]);
        return -1;
    }
    checkIn(argv[1]);
    Lst *lst = readAll(argv[1]);
    printLst(lst);
    printf("Done\n");

    return 0;
}
