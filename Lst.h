#ifndef LST_H
#define LST_H

char* skipSpace(char *in)
{
    while(in != NULL && *in != '\0' && isspace(*in))
        in++;
    return in;
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

void panic(char *message, char *pos)
{
    char *msg = message ? message : "No message";
    char *at = pos ? pos : "No pos";
    fprintf(stderr, "Error: \"%s\" at \"%s\"\n", msg, at);
    exit(EXIT_FAILURE);
}

Type getNext(char **pos)
{
    *pos = skipSpace(*pos);
    if(**pos == ')')
        return T_END;
    if(isalpha(**pos))
        return T_SYM;
    if(isdigit(**pos))
        return T_NAT;
    if(**pos == '(')
        return T_LST;

    panic("Unexpected char", *pos);
    return -1;
}

Lst* getSym(char **pos)
{
    Lst *lst = calloc(1, sizeof(Lst));
    char *cur = *pos;
    lst->type = T_SYM;
    while(isalpha(*cur))
        cur++;
    lst->sym = calloc((cur - *pos)+1, sizeof(char));
    memcpy(lst->sym, *pos, cur - *pos);
    return lst;
}

Lst* getNat(char **pos)
{
    Lst *lst = calloc(1, sizeof(Lst));
    char *cur = *pos;
    lst->type = T_NAT;
    while(isdigit(*cur)){
        lst->nat *= 10;
        lst->nat += *cur - '0';
        cur++;
    }
    return lst;
}

Lst *getLst(char **pos)
{
    Lst *lst = calloc(1, sizeof(Lst));
    lst->type = T_LST;
    (*pos)++;
}

Lst *readNxt(char **pos)
{
    while(**pos != '\0')
        switch(getNext(pos)){
            case T_END:
                *pos++;
                return NULL;
                break;
            case T_SYM:
                return getSym(pos);
                break;
            case T_NAT:
                return getNat(pos);
                break;
            case T_LST:

                break;
            default:
                panic("how did i get here and what do i do", *pos);
                break;
        }
    }
    return NULL;

    if(**pos == ')'){
        // printf(") %s\n", *pos);
        (*pos)++;
        *pos = skipSpace(*pos);
        return NULL;
    }
    Lst *lst = calloc(1, sizeof(Lst));
    if(isalpha(**pos)){
        // printf("s %s\n", *pos);
        char *cur = *pos;
        lst->type = T_SYM;
        while(isalpha(*cur))
            cur++;
        lst->sym = calloc((cur - *pos)+1, sizeof(char));
        memcpy(lst->sym, *pos, cur - *pos);
        *pos = skipSpace(cur);
    }else if(isdigit(**pos)){
        // printf("n %s\n", *pos);
        char *cur = *pos;
        lst->type = T_NAT;
        while(isdigit(*cur)){
            lst->nat *= 10;
            lst->nat += *cur - '0';
            cur++;
        }
        *pos = skipSpace(cur);
    }else if(**pos == '('){
        // printf("( %s\n", *pos);
        lst->type = T_LST;
        (*pos)++;
        *pos = skipSpace(*pos);
    }
    return lst;
}

void freeLst(Lst *lst)
{
    while(lst){
        switch(lst->type){
            case T_LST:
                freeLst(lst->lst);
                break;
            case T_SYM:
                free(lst->sym);
                break;
            default:
                break;
        }
        Lst *nxt = lst->nxt;
        free(lst);
        lst = nxt;
    }
}

Lst *readLst(char **pos)
{
    Lst *lst = NULL;
    Lst *cur = NULL;
    while((cur = readNxt(pos)) != NULL){
        if(cur->type == T_LST)
            cur->lst = readLst(pos);
        lst = append(lst, cur);
    }
    return lst;
}

void ind(const uint lvl)
{
    for(uint i = 0; i < lvl; i++)
        printf("\t");
}

void printLstLvlPos(Lst *lst, const uint lvl, uint pos)
{
    while(lst){
        switch(lst->type){
            case T_SYM:
                ind(lvl);
                printf("T_SYM @ %u,%u: %s\n", lvl, pos, lst->sym);
                break;
            case T_NAT:
                ind(lvl);
                printf("T_NAT @ %u,%u: %u\n", lvl, pos, lst->nat);
                break;
            case T_LST:
                ind(lvl);
                printf("T_LST @ %u,%u: (\n", lvl, pos);
                printLstLvlPos(lst->lst, lvl+1, 0);
                ind(lvl);
                printf(")\n");
                break;
        }
        pos++;
        lst = lst->nxt;
    }
}

void printLst(Lst *lst)
{
    printLstLvlPos(lst, 0, 0);
}

#endif /* end of include guard: LST_H */
