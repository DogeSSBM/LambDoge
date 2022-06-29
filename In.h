#ifndef IN_H
#define IN_H

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
bool checkIn(char *in, const bool throw)
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
            if(throw)
                exit(EXIT_FAILURE);
            return false;
        }
        pos++;
    }
    // parens balanced
    if(bal == 0)
        return true;
    fprintf(stderr, "Unclosed '(' at \"%s\"\n", last);
    showErr(in, last);
    if(throw)
        exit(EXIT_FAILURE);
    return false;
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
        exit(EXIT_FAILURE);
    }
    return buf;
}

uint awaitNat(void)
{
    char *str;
    uint in;
    do{
        in = 0;
        str = awaitIn();
        while(isdigit(*str)){
            in *= 10;
            in += *str - '0';
            str++;
        }
    }while(*str != '\0');
    return in;
}

uint awaitIndex(const uint max)
{
    uint ret;
    printf("Enter index [0, %u]:\n", max-1);
    while((ret = awaitNat()) >= max){
        printf("Must be > 0 and <= %u\n", max-1);
    }
    return ret;
}

#endif /* end of include guard: IN_H */
