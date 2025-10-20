#include <stdint.h>
#include <stdio.h>

#include "hashMap.h"

/**
 * Function used to hash any pointer to a 64 bit integer
 * 
 * @param value pointer to the value
 * @param size the size that value holds
 * 
 * @return Success: a 64 bit hash | Failure: NULL
 */
int64_t hash(void *value, int size);

int64_t hash(void *value, int size)
{
    if(value == NULL){
        printf("[ERROR] : value is null | hash \n");
        return NULL;
    }

    int64_t initialHash = 4366080005767977372;

    int iterations = (size/8) + 1;
    int pos = 0;
    int8_t *pValue = (int*)value;

    for(int i = 0; i < iterations && i < 16; i++){
        int chunkSize = 8;
        if(size - pos < 8){
            chunkSize = size - pos;
        }

        int64_t chunkValue = 0;

        for(int j = 0; j < chunkSize; j++){
            chunkValue |= ((int64_t)pValue[pos + j]) << (8 * j);
        }

        initialHash ^= chunkValue;

        pos += chunkSize;

        if(pos >= size){
            break;
        }
    }

    return initialHash;
}
