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
    while(in != NULL && *in != '\0' && isspace(*in))
        in++;
    return in;
}

Lst *readNat(char **in)
{
    char *pos = *in;
    Lst *lst = calloc(1, sizeof(Lst));
    lst->type = T_NAT;
    while(isdigit(*pos)){
        lst->nat *= 10;
        lst->nat += *pos - '0';
        pos++;
    }
    *in = skipSpace(pos);
    return lst;
}

Lst *readSym(char **in)
{
    char *pos = *in;
    char *end = *in;
    Lst *lst = calloc(1, sizeof(Lst));
    lst->type = T_SYM;
    while(isalpha(*end))
        end++;
    lst->sym = calloc((end-pos)+1, sizeof(char));
    memcpy(lst->sym, pos, end-pos);
    *in = skipSpace(end);
    return lst;
}

Lst *append(Lst *head, Lst *tail)
{
    if(head == NULL)
        return tail;
    Lst *cur = head;
    while(cur->nxt)
        cur = cur->nxt;
    cur->nxt = tail;
    return head;
}

Lst *readLst(char **in)
{
    char *pos = *in;
    Type t;
    Lst *lst;
    while((t = getType(*(pos = skipSpace(pos))))!=T_NIL){
        switch(t){
            case T_NAT:
                lst = append(lst, readNat(&pos));
                break;
            case T_SYM:
                lst = append(lst, readSym(&pos));
                break;
            case T_LST:
                lst = append(lst, readLst(&pos));
                break;
            default:
                printf("somethin borked yo\n");
                exit(-1);
        }
    }
    return lst;
}

void printLst(Lst *lst)
{
    printf("( ");
    while(lst){
        switch(lst->type){
            case T_NAT:
                printf("%u ", lst->nat);
                break;
            case T_SYM:
                printf("%s ", lst->sym);
                break;
            case T_LST:
                printLst(lst->lst);
                break;
            default:
                printf("somethin borked yo\n");
                exit(-1);
        }
        lst = lst->nxt;
    }
    printf(")\n");
}
