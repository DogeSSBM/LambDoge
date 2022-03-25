#pragma once

void ind(const uint lvl)
{
    for(uint i = 0; i < lvl; i++)
        printf("\t");
}


// returns the number of navable lists
uint printNav(Lst *lst)
{
    (void)lst;
    // while(lst){}
    return 1;
}
