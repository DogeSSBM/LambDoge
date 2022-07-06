#ifndef TESTLST_H
#define TESTLST_H

void panicAt(const char *message, const char *pos)
{
    const char *msg = message ? message : "No message";
    const char *at = pos ? pos : "No pos";
    fprintf(stderr, "Error: \"%s\" at \"%s\"\n", msg, at);
    exit(EXIT_FAILURE);
}

void panic(const char *message)
{
    fprintf(stderr, "Error: \"%s\"\n", message);
    exit(EXIT_FAILURE);
}

void testLst(char **allIn, const uint numIn)
{
    uint correct = 0;
    printf("+==================+====================+==================+\n");
    printf("|##################|  Begin All Tests   |##################|\n");
    printf("+==================+====================+==================+\n");
    for(uint i = 0; i < numIn; i++){
        if(i>0)
            printf("+------------------+--------------------+------------------+\n");
        printf("|                  |        %02u/%02u       |                  |\n", i+1, numIn);
        printf("+------------------+--------------------+------------------+\n");

        char *in = allIn[i];
        if(!in)
            panic("Input NULL");
        printf("Input: \"%s\"\n", in);
        printf("Checking parens...\n");
        const bool valid = checkIn(in, false);
        correct += valid;
        printf("...Done checking!\n");
        if(valid){
            printf("Parsing Lst...\n");
            Lst *lst = readLst(&in);
            printf("...Done parsing!\n");
            printf("Printing Lst...\n");
            printLst(lst);
            printf("...Done printing!\n");
            printf("Freeing Lst...\n");
            freeLst(lst);
            printf("...Done freeing!\n");
        }else{
            printf("Unbalanced parens, skipping Lst parsing\n");
        }
        printf("+------------------+--------------------+------------------+\n");
        printf("|                  |        Done        |                  |\n");
    }
    printf("+==================+====================+==================+\n");
    printf("|##################|                    |##################|\n");
    printf("|##################|       %02u/%02u        |##################|\n", correct, numIn);
    printf("|##################|                    |##################|\n");
    printf("+==================+====================+==================+\n");
}

#endif /* end of include guard: TESTLST_H */
