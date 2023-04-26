//////////////////////////////////////////////////////////////////////////
///
/// Copyright (c) 2020 Prof. AJ Bieszczad. All rights reserved.
///
//////////////////////////////////////////////////////////////////////////

#include "disk.h"

disk_t disk;

/***
 *
 * Verifies correctness of the logical block address, and then translates it to a cylinder-head-sector equivalent.
 *
 */
CIDEV_RET_CODE lba2chs(lba_t lba, chs_t *chs)
{
    if (lba > MAX_LOGICAL_BLOCK){
        return CIDEV_ADDRESS_ERROR;
    }
// todo: implement
    chs->cyl = lba/(NUM_OF_HEADS*NUM_OF_SECTS);
    chs->head = lba%(NUM_OF_HEADS*NUM_OF_SECTS)/(NUM_OF_SECTS);
    chs->sect = lba%(NUM_OF_SECTS);

    return CIDEV_SUCCESS;
}

/***
 *
 * Verifies correctness of the cylinder-head-sector address, and then translates it to a logical block address.
 *
 */
CIDEV_RET_CODE chs2lba(chs_t *chs, lba_t *lba)
{
// todo: implement
    if(chs->cyl > NUM_OF_CYLS || chs->head > NUM_OF_HEADS || chs->sect > NUM_OF_SECTS){
        return CIDEV_ADDRESS_ERROR;
    }
    *lba = chs->cyl*(NUM_OF_HEADS*NUM_OF_SECTS) + chs->head*(NUM_OF_SECTS) + chs->sect;

    return CIDEV_SUCCESS;
}
/***
 *
 * Verifies the parameters, then allocates space for the requested data (using
 * the caller-provided pointer buffer), copies the data from the disk to the buffer,
 * and appends '\0' to terminate the string.
 *
 */
CIDEV_RET_CODE readDisk(lba_t lba, unsigned int size, char **buffer)
{
    // todo: verify parameters
    if (lba >= MAX_LOGICAL_BLOCK){
        return CIDEV_ADDRESS_ERROR;
    }
    if(lba + size > MAX_LOGICAL_BLOCK){
        return CIDEV_SPACE_ERROR;
    }

    int numberOfReads = size/SECT_SIZE;
    int i;
    
    chs_t chs;
    
    *buffer = malloc(size + 1); // todo: modify as required edit: allocate SECT_SIZE chars to the buffer array
    for(i = 0; i < numberOfReads; i++){
        lba2chs(lba + (i),&chs);
        memcpy(((*buffer) + (i*SECT_SIZE)), disk[chs.cyl][chs.head][chs.sect], SECT_SIZE);
    } //nice
    if(size%SECT_SIZE != 0){
        lba2chs(lba + i, &chs);
        memcpy((*buffer) + (numberOfReads*SECT_SIZE), disk[chs.cyl][chs.head][chs.sect + size], size % SECT_SIZE);
    }
    *((buffer) + size) =  '\0';

    return CIDEV_SUCCESS;
}

/***
 *
 * An auxiliary function to fill a single disk block with '.'
 *
*/
CIDEV_RET_CODE clearBlock(lba_t lba)
{
    char *writeBuffer;
#ifdef __DEBUG_DISK
    writeBuffer = malloc(SECT_SIZE);
#else
    writeBuffer = kmalloc(SECT_SIZE, GFP_USER);
#endif
    if (writeBuffer == NULL)
        return CIDEV_SPACE_ERROR;

    for (int i = 0; i < SECT_SIZE; i++)
        writeBuffer[i] = '.';

    CIDEV_RET_CODE errCode = writeDisk(lba, writeBuffer);

#ifdef __DEBUG_DISK
    free(writeBuffer);
#else
    kfree(writeBuffer);
#endif

    return errCode;
}

/***
 *
 * Validates the parameters, and then writes the caller-provided data to the disk starting at the block pointed
 * to by the logical block address.
 *
 */
CIDEV_RET_CODE writeDisk(lba_t lba, char *buffer)
{
    // todid: verify the parameters
    if (lba + strlen(buffer) >= MAX_LOGICAL_BLOCK){
        return CIDEV_ADDRESS_ERROR;
    }
    chs_t chs;
    int size = strlen(buffer);
    int numberOfWrites = size/SECT_SIZE;
    int i;

    for(i = 0; i < numberOfWrites; i++){
        if(lba2chs(lba + (i), &chs) == CIDEV_ADDRESS_ERROR){
            return CIDEV_ADDRESS_ERROR;
        }
        memcpy(disk[chs.cyl][chs.head][chs.sect], buffer + (i*SECT_SIZE), SECT_SIZE);
        
    }
    if(size % SECT_SIZE !=0){
            lba2chs(lba + i, &chs);
            memcpy(disk[chs.cyl][chs.head][chs.sect], buffer + (i *SECT_SIZE), size % SECT_SIZE);
    }    
    return CIDEV_SUCCESS;
}
