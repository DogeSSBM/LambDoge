#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "Lst.h"
#include "In.h"
#include "Nav.h"

int main(int argc, char *argv[])
{
    if(argc != 2){
        fprintf(stderr, "Usage:\n%s \"<Input Lst>\"\n\n", argv[0]);
        fprintf(stderr, "Example:\n%s \"()\"\n", argv[0]);
        return -1;
    }
    char *in = argv[1];
    checkIn(in);
    Lst *lst = readLst(&in);
    printLst(lst, 0);
    printf("Done\n");

    return 0;
}
