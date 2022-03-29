#pragma once

void clear(void)
{
    printf("\033[1;1H\033[2J");
}

// prints only the current list omitting sublists
void printLvl(Lst *lst)
{
    // uint cur = 0;
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
        }
        lst = lst->nxt;
    }
    printf("\n");
}

uint lvlIndOff(Lst *lvl, const uint ind)
{
    uint curind = 0;
    Lst *curlst = lvl;
    char buf[32] = {0};
    uint off = 0;
    while(curind < ind){
        if(!curlst){
            fprintf(stderr, "Index %u out of bounds (%u)\n", curind, lvlLen(lvl));
            printLvl(lvl);
            exit(-1);
        }
        switch(curlst->type){
            case T_SYM:
                off += strlen(curlst->sym)+1;
                break;
            case T_NAT:
                memset(buf, '\0', 32);
                sprintf(buf, "%u", curlst->nat);
                off += strlen(buf)+1;
                break;
            case T_LST:
                off+= 4;
                break;
        }
        curlst = curlst->nxt;
        curind++;
    }
    return off;
}

void spaces(const uint len)
{
    for(uint i = 0; i < len; i++)
        printf(" ");
}

void printNav(Lst *lst, const uint index)
{
    if(index >= lvlLen(lst)){
        fprintf(stderr, "Index %u out of bounds (%u)\n", index, lvlLen(lst));
        printLvl(lst);
        exit(-1);
    }
    printLvl(lst);
    const uint off = lvlIndOff(lst, index);
    spaces(off);
    printf("^\n");
}

void nav(Lst *lst)
{
    uint index = 0;
    while(1){
        clear();
        printNav(lst, index);
        index = awaitIndex(lvlLen(lst));
    }
}
