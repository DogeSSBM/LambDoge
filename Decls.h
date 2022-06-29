#ifndef DECLS_H
#define DECLS_H

// IN_H
void showErr(char *, char *);
bool checkIn(char *, const bool);
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
void printLstInd(Lst *lst, const int );
void printLst(Lst *);

// TESTLST_H
void panicAt(char *, char *);
void panic(char *);
void testLst(char **, const uint);

#endif /* end of include guard: DECLS_H */
