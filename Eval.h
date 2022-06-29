#ifndef EVAL_H
#define EVAL_H

Lst *sum(Lst *lst)
{
    Lst *ret = calloc(1, sizeof(Lst));
    ret->type = T_NAT;
    while(lst){
        if(lst->type != T_NAT){
            fprintf(stderr, "cant sum lst with type %s\n", TypeStr[lst->type]);
            exit(EXIT_FAILURE);
        }
        ret->nat += lst->nat;
        lst = lst->nxt;
    }
    return ret;
}

Lst *searchEnv(char *name, const uint len)
{
    Lst *cur = env;
    while(cur){
        if(cur->type == T_SYM && strlen(cur->sym.name) == len && !strncmp(cur->sym.name, name, len))
            return cur;
        cur = cur->nxt;
    }
    return NULL;
}

#endif /* end of include guard: EVAL_H */
