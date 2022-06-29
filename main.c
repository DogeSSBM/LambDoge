#include "Includes.h"

int main(int argc, char *argv[])
{
    if(argc != 2){
        fprintf(stderr, "Usage:\n%s \"<Input Lst>\"\n\n", argv[0]);
        fprintf(stderr, "Example:\n%s \"()\"\n", argv[0]);
        return -1;
    }

    // #include "TestInclude.doge"

    env = calloc(1, sizeof(Lst));
    env->type = T_SYM;
    env->sym.name = "sum";
    

    char *in = argv[1];
    checkIn(in, true);
    // Lst *lst = NULL;
    // Lst *cur;
    //     while((cur = readNxt(&in))){
    //     lst = append(lst, cur);
    // }
    Lst *lst = readLst(&in);
    printLst(lst);
    freeLst(lst);
    printf("Done\n");

    return 0;
}
