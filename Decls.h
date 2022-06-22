#ifndef DECLS_H
#define DECLS_H

// IN_H
void showErr(char *, char *);
void checkIn(char *);
char *awaitIn(void);
uint awaitNat(void);
uint awaitIndex(const uint);

// LST_H
char* skipSpace(char *);
Lst *append(Lst *head, Lst *);
Lst *readNxt(char **);
void freeLst(Lst *);
Lst *readLst(char **);
void ind(const uint );
void printLstLvlPos(Lst *lst, const uint, uint);
void printLst(Lst *);

#endif /* end of include guard: DECLS_H */
