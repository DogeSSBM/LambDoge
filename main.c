#include "Includes.h"

int main(int argc, char *argv[])
{
    // if(argc != 2){
    //     fprintf(stderr, "Usage:\n%s \"<Input Lst>\"\n\n", argv[0]);
    //     fprintf(stderr, "Example:\n%s \"()\"\n", argv[0]);
    //     return -1;
    // }
    (void)argc;
    (void)argv;
    Lst *lst = fileReadLst("Test00.doge");
    printLst(lst);
    freeLst(lst);
    printf("Done 00\n");
    lst = fileReadLst("Test01.doge");
    printLst(lst);
    freeLst(lst);
    printf("Done 01\n");

    return 0;
}
