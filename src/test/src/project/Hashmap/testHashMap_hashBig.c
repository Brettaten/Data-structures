#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashMap.h"

typedef struct BigObj
{
    char *str;
    int id;
} BigObj;


void add(HashMap *pMap);

void addBig(HashMap *pMap, char *cp);

void *copyBig(void *big);

void freeBig(void *big);

uint64_t hashBig(void *value, int size);

bool equalsBig(void *value1, void *value2, int size);












uint64_t hashBig(void *big, int size)
{
    BigObj *pBig = (BigObj *)big;

    char *str = pBig->str;
    int id = pBig->id;

    uint64_t hashStr = hash(str, sizeof(char)*2);
    uint64_t hashId = hash(&id, sizeof(int));

    return hashStr ^ hashId;
}
