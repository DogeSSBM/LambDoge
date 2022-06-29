#ifndef PRINT_H
#define PRINT_H

void ind(const uint lvl)
{
    for(uint i = 0; i < lvl; i++)
        printf("\t");
}

void printLstfHelper(Lst *lst, const PrintFlags flags, const uint lvl, uint pos)
{
    while(lst){
        if(flags & P_IND)
            ind(lvl);
        if(flags & P_TYPE)
            printf("%s", TypeStr[lst->type]);
        if(flags & P_LVL || flags & P_POS)
            printf(" @ ");
        if(flags & P_LVL)
            printf("%u", lvl);
        if(flags & P_LVL && flags & P_POS)
            printf(",");
        if(flags & P_POS)
            printf("%u", pos);
        printf(": ");
        if(flags & P_VAL){
            switch(lst->type){
                case T_SYM:
                    printf("%s", lst->sym);
                    if(flags & P_NL)
                        printf("\n");
                    break;
                case T_NAT:
                    printf("%u", lst->nat);
                    if(flags & P_NL)
                        printf("\n");
                    break;
                case T_LST:
                    printf("(");
                    if(flags & P_NL)
                        printf("\n");
                    printLstfHelper(lst->lst, flags, lvl+1, 0);
                    if(flags & P_IND)
                        ind(lvl);
                    printf(")");
                    if(flags & P_NL)
                        printf("\n");
                    break;
                default:
                    printf("UNKNOWN type\n");
                    exit(EXIT_FAILURE);
                    break;
            }
        }
        pos++;
        lst = lst->nxt;
    }
    if(!(flags & P_NL))
        printf("\n");
}

void printLstf(Lst *lst, const PrintFlags flags)
{
    printLstfHelper(lst, flags, 0, 0);
}

void printLst(Lst *lst)
{
    printLstfHelper(lst, P_ALL, 0, 0);
}

#endif /* end of include guard: PRINT_H */
