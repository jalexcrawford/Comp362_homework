#ifndef REPLACE_LRULIST_H
#define REPLACE_LRULIST_H

#include "replace.h"

// the page frame list
typedef struct frame {
    int pageNumber;
    struct frame *back; //update because my brain is breaking on up/down convention
    struct frame *next; //ibid
} FRAME;

void insertLRU(int);
FRAME *searchLRU(int);
void displayLRU(void);
void freePageTableLRU(void);

#endif //REPLACE_LRULIST_H
