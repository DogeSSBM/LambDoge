#ifndef TESTLST_H
#define TESTLST_H

void panicAt(char *message, char *pos)
{
    char *msg = message ? message : "No message";
    char *at = pos ? pos : "No pos";
    fprintf(stderr, "Error: \"%s\" at \"%s\"\n", msg, at);
    exit(EXIT_FAILURE);
}

void panic(char *message)
{
    fprintf(stderr, "Error: \"%s\"\n", message);
    exit(EXIT_FAILURE);
}

void testLst(const char **allIn, const uint numIn)
{
    printf("<=<<=<<=||Begin All Tests||=>>=>>=>\n");
    for(uint i = 0; i < numIn; i++){
        printf("<-<<-<<-||Begin test input %02u/%02u||->>->>->\n", i+1, numIn);
        char *in = allIn[i];
        if(!in)
            panic("Input NULL");
        printf("Input: \"%s\"\n", in);
        printf("Checking parens...\n");
        checkIn(in);
        printf("\t...Done!\n");
        printf("Parsing Lst...\n");
        Lst *lst = readLst(&in);
        printf("\t...Done!\n");
        printf("Printing parsed Lst...\n");
        printLst(lst);
        printf("\t...Done!\n");
        printf("Freeing Lst...\n");
        freeLst(lst);
        printf("\t...Done!\n");
        printf("<-<<-<<-||Done! input %02u/%02u||->>->>->\n\n", i+1, numIn);
    }
    printf("<=<<=<<=||Done! All Tests||=>>=>>=>\n");
}

#endif /* end of include guard: TESTLST_H */
