#pragma once

// prints only the current list omitting sublists
void printLvl(Lst *lst)
{
    uint cur = 0;
    while(lst){
        switch(lst->type){
            case T_SYM:
                printf("%s ", lst->sym);
                break;
            case T_NAT:
                printf("%u ", lst->nat);
                break;
            case T_LST:
                printf("(_) ");
                break;
        lst = lst->nxt;
    }
    printf("\n");
}

Lst *lvlInd(Lst *lvl, const uint ind)
{
    uint curind = 0;
    Lst *curlst = lvl;
    while(curind < ind){
        if(!curlst){
            fprintf(stderr, "Index %u out of bounds (%u)\n", curind, lvlLen(lvl));
            printLvl(lvl);
            exit(-1)
        }
        curlst = curlst->nxt;
        curind++;
    }
    return curlst;
}

uint lvlIndOff(Lst *lvl, const uint ind)
{
    uint curind = 0;
    Lst *curlst = lvl;
    uint off = 0;
    while(curind < ind){
        if(!curlst){
            fprintf(stderr, "Index %u out of bounds (%u)\n", curind, lvlLen(lvl));
            printLvl(lvl);
            exit(-1)
        }
        switch(curlst){
            case T_SYM:
                off += strlen(curlst->sym)+1;
                printf("%s ", lst->sym);
                break;
            case T_NAT:
                
                printf("%u ", lst->nat);
                break;
            case T_LST:
                printf("(_) ");
                break;
        }
        curlst = curlst->nxt;
        curind++;
    }
    return curlst;
}

char *awaitIn(void)
{
    static char buf[1024] = {0};
    memset(buf, '\0', 1024);
    uint i = 0;
    int c;
    while(i < 1023 && (c = fgetc(stdin)) != '\n'){
        buf[i] = c;
        i++;
    }
    if(i >= 1024){
        fprintf(stderr, "Input must be < 1024 chars\n");
        exit(-1)
    }
    return buf;
}

Lst *navLst(Lst *lst)
{

}
