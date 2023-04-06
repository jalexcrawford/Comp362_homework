/**
 * This implements the LRU page-replacement algorithm.
 */

#include "../inc/lruList.h"

int *referenceString;
int refStringLength;

FRAME *pageTableTop;
FRAME *leastRecentlyUsed;
int pageTableSize;

int numberOfFramesPerProcess = 0;

// statistics
int nummberOfFaults = 0;

int hitPageNumber;

/*
 * insert pages from a reference string into a page table and measure
 * the page fault rate
 */
int testLRU(int numOfFrames, int *refString, int refStrLen)
{
    for(int i = 0; i < refStrLen; i++){
        //look for frame in page table
        FRAME* searchFrame = searchLRU(refString[i]);
        if(searchFrame == NULL){
            insertLRU(refString[i]);
            nummberOfFaults -= -1; // using -= -1 because this breaks for some reason otherwise ಠ_ಠ
        }else{
            //frame is in page table 
            searchFrame->up->down = searchFrame->down;
            searchFrame->down->up = searchFrame->up;
            searchFrame->up = NULL;
            searchFrame->down = pageTableTop;
            pageTableTop->up = searchFrame;
        }

    }
    return nummberOfFaults;
}

/*
 *	try to insert a page into the page table
 */
void insertLRU(int pageNumber)
{
    FRAME* newFrame = malloc(sizeof(FRAME));

    if(pageTableTop != NULL){
        newFrame->down = pageTableTop;
        pageTableTop->up = newFrame;
    }
    pageTableTop = newFrame;
    
}

/**
 * Searches for page pageNumber in the page frame list
 * returns NULL if a frame with pageNumber was not found
 * otherwise, returns a reference to the frame with pageNumber
 */
FRAME *searchLRU(int pageNumber)
{
    FRAME* foundFrame = pageTableTop;

    while(foundFrame->down != NULL){
        if(foundFrame->pageNumber == pageNumber){
            return foundFrame;
        }else{
            foundFrame = foundFrame->down;
        }
    }
    return NULL;
}

void displayLRU()
{
    FRAME* walkingFrame = pageTableTop;
    while(walkingFrame != NULL){
        printf("%d\t",walkingFrame->pageNumber);
        walkingFrame = walkingFrame->down;
    }
}

void freePageTableLRU()
{
    // TODO: implement
}

