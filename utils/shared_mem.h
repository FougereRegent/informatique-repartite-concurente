#ifndef _SHARED_MEM_H
#define _SHARED_MEM_H

#define ERROR_ADD_ELEMENT -1

typedef struct {
  int size;
  int descriptor;
  int *adresse;
} MemoirePartagee;

extern MemoirePartagee superMalloc(const int taille);
extern int superFree(MemoirePartagee *m);
extern void addElement(MemoirePartagee *m, const int value);
extern int *readElements(MemoirePartagee *m);

#endif
