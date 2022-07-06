#ifndef FILE_H
#define FILE_H

uint fileLen(const char *filePath)
{
    if(!filePath)
        panic("Cannot open NULL file path");
    File *f = fopen(filePath, "r");
    if(!f)
        panicAt("Could not open file at", filePath);
    int c = ' ';
    uint len = 0;
    while((c = fgetc(f)) != EOF)
        len++;
    fclose(f);
    return len;
}

char* fileReadText(const char *filePath)
{
    const uint len = fileLen(filePath);
    char *buf = calloc(len+1, sizeof(char));
    buf[len] = '\0';
    if(!filePath)
        panic("Cannot open NULL file path");
    File *f = fopen(filePath, "r");
    if(!f)
        panicAt("Could not open file at", filePath);
    int c = ' ';
    uint pos = 0;
    while((c = fgetc(f)) != EOF){
        buf[pos] = c;
        pos++;
    }
    fclose(f);
    if(c == EOF && pos != len)
        panic("Size mismatch");
    return buf;
}

bool isCommentLine(char *in)
{
    if(!in)
        panic("NULL input cannot be comment");
    return !strncmp(in, "\n--", 3);
}

char *sanatize(char *in)
{
    if(!in)
        panic("Cannot sanatize NULL input");
    char *cur = in;
    while(*(cur++)  != '\0'){
        if(isCommentLine(cur)){
            do
                *cur = ' ';
            while(*(cur++) != '\n' && *cur != '\0');
        }
    }
    return in;
}

Lst *fileReadLst(const char *filePath)
{
    char *in = fileReadText(filePath);
    in = sanatize(in);
    checkIn(in, true);
    return readLst(&in);
}

#endif /* end of include guard: FILE_H */
