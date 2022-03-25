#pragma once

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

// 1    0 1   0 12 1 2 3   21   <-bal
// (asdf)(asdf) ((s) (2(234))   <-in
//              ^               <-last
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

char *readNat(uint *nat, char *in)
{
    *nat = 0;
    while(isdigit(*in)){
        *nat *= 10;
        *nat += *in - '0';
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

char *readNil(char *in)
{
    if(*in != ')')
        printf("???????\n");
    return skipSpace(in+1);
}

char *readLstBAD(Lst **tail, char *in)
{
    Lst *lst = *tail;
    do{
        switch(lst->type = getType(*in)){
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
                in = readNil(in);
                return in;
            case T_ERR:
            default:
                fprintf(stderr, "Unknown type starting at \"%s\"\n", in);
                exit(-1);
        }
        lst->nxt = calloc(1, sizeof(Lst));
        skipSpace(in);
        lst = lst->nxt;
    }while(in != NULL && *in != '\0');
    return NULL;
}


void ind(const uint lvl)
{
    for(uint i = 0; i < lvl; i++)
        printf("\t");
}

void printLst(Lst *lst)
{
    static int lvl = 0;
    while(lst){
        switch(lst->type){
            case T_NAT:
                ind(lvl);
                printf("%u\n", lst->nat);
                lst = lst->nxt;
                break;
            case T_SYM:
                ind(lvl);
                printf("%s\n", lst->sym);
                lst = lst->nxt;
                break;
            case T_LST:
                ind(lvl);
                printf("(\n");
                lvl++;
                printLst(lst->lst);
                lst = lst->nxt;
                break;
            case T_NIL:
                lvl--;
                if(lvl<0){
                    fprintf(stderr, "How yo!?!?!\n");
                    exit(-1);
                }
                ind(lvl);
                printf(")\n");
                return;
                break;
            default:
                fprintf(stderr, "How yo!?!?!\n");
                exit(-1);
                break;
        }
    }
}
