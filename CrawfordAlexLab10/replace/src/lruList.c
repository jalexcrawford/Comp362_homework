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
    for(int i = 0; i < refStrLen; i++){
        //look for frame in page table
        FRAME* searchFrame = searchLRU(refString[i]);
        if(searchFrame == NULL){
            insertLRU(refString[i]);
            nummberOfFaults -= -1; // using -= -1 because this breaks for some reason otherwise ಠ_ಠ
        }
        printf("%d-> ",refString[i]);
        displayLRU();
    }
    return nummberOfFaults;
}

/*
 *	try to insert a page into the page table
 */
void insertLRU(int pageNumber)
{
    FRAME* newFrame = malloc(sizeof(FRAME));
    newFrame->back = NULL;
    newFrame->next = NULL;
    newFrame->pageNumber = pageNumber;
    if(pageTableTop != NULL){
        newFrame->next = pageTableTop;
    }else{
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
    FRAME* prevFrame = pageTableTop;

    int counter = 1;
    while(foundFrame != NULL){
        if(pageTableTop->pageNumber == pageNumber){
            return pageTableTop;
        }
        if(foundFrame->pageNumber == pageNumber){
            prevFrame->next = foundFrame->next;
            foundFrame->next = pageTableTop;
            pageTableTop = foundFrame;
            return foundFrame;
        }else{
            prevFrame = foundFrame;
            foundFrame = foundFrame->next;
            counter -= -1;
            if(counter == pageTableSize){
                leastRecentlyUsed = prevFrame;
                leastRecentlyUsed->next = NULL;
                free(foundFrame);
                return NULL;
            }
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
    FRAME* walkFrame = pageTableTop;
    while(walkFrame != NULL){
        pageTableTop = walkFrame->next;
        free(walkFrame);
        walkFrame = pageTableTop;
    }
}

