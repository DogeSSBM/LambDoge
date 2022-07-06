#ifndef DECLS_H
#define DECLS_H

// PRINT_H
void ind(const uint);
void printLstfHelper(Lst *, const PrintFlags, const uint, uint);
void printLstf(Lst *, const PrintFlags);
void printLst(Lst *);

// IN_H
void showErr(char *, char *);
bool checkIn(char *, const bool);
char *awaitIn(void);
uint awaitNat(void);
uint awaitIndex(const uint);

// FILE_H
char* fileReadText(const char *);

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
void panicAt(const char *, const char *);
void panic(const char *);
void testLst(char **, const uint);

// EVAL_H
// Lst *sum(Lst *);
// Lst *searchEnv(char *, const uint );

#endif /* end of include guard: DECLS_H */
