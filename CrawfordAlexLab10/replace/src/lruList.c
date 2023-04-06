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
    pageTableSize = numOfFrames;
    FRAME* prevFrame = NULL;
    for(int i = 0; i < refStrLen; i++){
        //look for frame in page table
        displayLRU();
        FRAME* searchFrame = searchLRU(refString[i]);
        if(searchFrame == NULL){
            insertLRU(refString[i]);
            nummberOfFaults -= -1; // using -= -1 because this breaks for some reason otherwise ಠ_ಠ
        }else{
            //frame is in page table 
            prevFrame->next = searchFrame->next;
            searchFrame->next = pageTableTop;
        }
        prevFrame = searchFrame;
    }
    return nummberOfFaults;
}

/*
 *	try to insert a page into the page table
 */
void insertLRU(int pageNumber)
{
    FRAME* newFrame = malloc(sizeof(FRAME));
    newFrame->back = NULL; //initializing because I'm not using it, but don't want something to break because it's not initialized.
    newFrame->next = NULL;
    newFrame->pageNumber = pageNumber;
    if(pageTableTop != NULL){
        newFrame->next = pageTableTop;
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

    int counter = 0;
    while(foundFrame != NULL){
        if(foundFrame->pageNumber == pageNumber){
            return foundFrame;
        }else{
            foundFrame = foundFrame->next;
            counter -= -1;
        }
        if(counter == pageTableSize){
            leastRecentlyUsed = foundFrame;
            return NULL;
        }
    }
    return NULL;
}

void displayLRU()
{
    FRAME* walkingFrame = pageTableTop;
    while(walkingFrame != NULL){
        printf("%d\t",walkingFrame->pageNumber);
        walkingFrame = walkingFrame->next;
    }
    printf("\n");
}

void freePageTableLRU()
{
    // TODO: implement
}

