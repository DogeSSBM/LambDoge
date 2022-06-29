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

Lst *readNxt(char **pos)
{
    if(**pos == ')') {
        // printf(") %s\n", *pos);
        (*pos)++;
        *pos = skipSpace(*pos);
        return NULL;
    }
    if(**pos == '\0')
        return NULL;
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

#endif /* end of include guard: LST_H */
