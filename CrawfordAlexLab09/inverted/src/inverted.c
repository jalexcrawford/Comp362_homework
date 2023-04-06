#include "../inc/inverted.h"

// "hidden" symbols (i.e., not included in the .h file)

int tableSize;
int frameSize;

int lookUp(PROC *, int, int);
int findOldest(PROC *table);

/*
 * initializes the table for the given sizes of the memory and frame
 * all entries should be zeroed (e.g., calloc())
 */
void initInverted(PROC **table, int msize, int fsize)
{
    tableSize = msize / fsize;
    frameSize = fsize;
    *table = calloc(tableSize, sizeof(PROC));
}


/*
 * translate a logical address <pid, page, offset> into a physical address
 * if there is no entry for the pid and the page number in the table, it has to be added
 * if there is no room in the table for the new entry, then the oldest entry has to be removed
 */
long translate(PROC *table, int pid, int page, int offset)
{
    long address = 0;
    int index = lookUp(table,pid,page);

    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);

    address = index*frameSize + offset;
    table[index].page = page;
    table[index].pid = pid;
    table[index].timeStamp = time.tv_sec * 1000000000 +time.tv_nsec;
    return address;

}

//
// find the entry for a given pid and page
//
int lookUp(PROC *table, int pid, int page)
{
    for(int i = 0; i < tableSize; i++){
        if(table[i].page == page){
            if(table[i].pid == pid){
                return i;
            }
        }
    }
    return findOldest(table);
}

//
// find the oldest entry (or not used that has the timestamp == 0)
//
int findOldest(PROC *table)
{
    time_t oldest;
    time(&oldest);
    int replacePosition = 0;
    for(int i = 0; i < tableSize; i++){
        if(table[i].timeStamp == 0){
            return i;
        }else if(table[i].timeStamp < oldest){
            oldest = table[i].timeStamp;
            replacePosition = i;
        }
    }
    return replacePosition;
}


/***
 * prints the inverted table
*/
void printInverted(PROC *table)
{
    printf("-------------------------------------\n");
    printf("        INVERTED TABLE CONTENT\n");
    printf("-------------------------------------\n");
    printf("| PID | PAGE |       TIMESTAMP\n");
    printf("-------------------------------------\n");
    for (int i = 0; i < tableSize; i++)
        printf("| %3d | %4d | %20ld |\n", table[i].pid, table[i].page, table[i].timeStamp);
}
