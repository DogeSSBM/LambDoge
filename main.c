#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "Lst.h"
#include "Nav.h"

int main(int argc, char *argv[])
{
    if(argc != 2){
        fprintf(stderr, "Usage:\n%s \"<Input Lst>\"\n\n", argv[0]);
        fprintf(stderr, "Example:\n%s \"()\"\n", argv[0]);
        return -1;
    }
    checkIn(argv[1]);
    Lst *lst = readLst(&argv[1]);
    printLst(lst);
    printf("Done\n");

    return 0;
}
