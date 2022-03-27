#pragma once

void showErr(char *in, char *err)
{
    const uint len = err-in;
    printf("%s\n", in);
    for(uint i = 0; i < len; i++)
        printf(" ");
    printf("^\n");
}

// 1    0 1   0 12 1 2 3   21   <-bal
// (asdf)(asdf) ((s) (2(234))   <-in
//              ^               <-last
// ensures input parens are properly formatted and balanced
void checkIn(char *in)
{
    char *pos = in;
    int bal = 0;
    char *last;
    while((pos = strpbrk(pos, "()"))){
        if(bal == 0)
            last = pos;
        if(*pos=='(')
            bal++;
        else
            bal--;
        if(bal < 0){
            fprintf(stderr, "Unexpected ')' at \"%s\"\n", pos);
            showErr(in, pos);
            exit(-1);
        }
        pos++;
    }
    // parens balanced
    if(bal == 0)
        return;
    fprintf(stderr, "Unclosed '(' at \"%s\"\n", last);
    showErr(in, last);
    exit(-1);
}
